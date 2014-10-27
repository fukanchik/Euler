#ifdef __number_h__
#error "Double inclusion of number.h!"
#endif
#define __number_h__

/* # of decimal digits in 'num'. */
int num_len(int num);
/* A lowest power of 10 which is greater than 'num'. */
int num_upto(int num);
/* n1|n2 */
int num_concat(int n1, int n2);
