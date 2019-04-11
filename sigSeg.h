#ifndef _SIG_SEG_H
#define _SIG_SEG_H


struct SigSeg {};
typedef void (*handler)();
void init_segv(handler h);


#endif // _SIG_SEG_H
