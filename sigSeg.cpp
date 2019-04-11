#include "sigSeg.h"

#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>


//using namespace std;

namespace
{

handler handler_segv = 0;

static void unblock_signal(int signum __attribute__((__unused__)))
{
    sigset_t sigs;
    sigemptyset(&sigs);
    sigaddset(&sigs, signum);
    sigprocmask(SIG_UNBLOCK, &sigs, NULL);
}

static void catch_segv (int, siginfo_t *, void *_p __attribute__ ((__unused__)))
{
    unblock_signal(SIGSEGV);
    handler_segv();
}

extern "C" 
{
  struct kernel_sigaction 
  {
    void (*k_sa_sigaction)(int,siginfo_t *,void *);
    unsigned long k_sa_flags;
    void (*k_sa_restorer) (void);
    sigset_t k_sa_mask;
  };
}

asm ( ".text\n" 
      ".byte 0  # Yes, this really is necessary\n" 
      ".align 16\n" "__" "restore_rt" ":\n" 
      "	movq $" "15" ", %rax  # Because __NR_rt_sigreturn = 15\n" 
      "	syscall\n" );

void restore_rt (void) asm ("__restore_rt") __attribute__ ((visibility ("hidden")));
}

void init_segv(handler h)
{
    if (h)
        handler_segv = h;
							
    struct kernel_sigaction act;				
    act.k_sa_sigaction = catch_segv;			
    sigemptyset (&act.k_sa_mask);				
    act.k_sa_flags = SA_SIGINFO|0x4000000;			
    act.k_sa_restorer = restore_rt;				
    syscall (SYS_rt_sigaction, SIGSEGV, &act, NULL, _NSIG / 8);	
}

