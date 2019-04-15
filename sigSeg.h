#ifndef _SIG_SEG_H
#define _SIG_SEG_H


struct SigSeg {};
typedef void (*handler)();
void init_segv(handler h, bool record_core_dumps);


#endif // _SIG_SEG_H
