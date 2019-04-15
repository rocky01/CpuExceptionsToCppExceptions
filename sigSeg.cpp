#include "sigSeg.h"

#include <signal.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/syscall.h>


namespace
{

handler handler_segv = 0;
bool record_core_dumps_ = false;
struct sigaction old_sa;

static void unblock_signal(int signum)
{
    sigset_t sigs;
    sigemptyset(&sigs);
    sigaddset(&sigs, signum);
    sigprocmask(SIG_UNBLOCK, &sigs, NULL);
}

static void catch_segv (int, siginfo_t *, void *)
{
    if ((!record_core_dumps_) || fork() > 0)
    {
      unblock_signal(SIGSEGV);
      handler_segv();
    }			
    else 
    {	
       if (sigaction(SIGSEGV, &old_sa, NULL) == -1)
          abort();	
    }
}

} // namespace

void init_segv(handler h, bool record_core_dumps)
{
    if (h)
    {
        record_core_dumps_ = record_core_dumps;
        handler_segv = h;
        struct sigaction sa;
        sa.sa_sigaction = catch_segv;
        sa.sa_flags = SA_SIGINFO|0x4000000;
        sigemptyset(&sa.sa_mask);
        if (sigaction(SIGSEGV, &sa, &old_sa) == -1)
            abort();
    }
}
