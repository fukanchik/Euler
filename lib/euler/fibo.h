#ifdef __fibo_h__
#error "Double inclusion of fibo.h!"
#endif
#define __fibo_h__

#include <euler/large.h>

void large_fibo_init();
void large_fibo(struct large* out, int num);
