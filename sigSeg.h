#ifndef _SIG_SEG_H
#define _SIG_SEG_H

#include <signal.h>

void init_segv(sighandler_t h, bool record_core_dumps);

#endif // _SIG_SEG_H
