#ifdef __number_h__
#error "Double inclusion of number.h!"
#endif
#define __number_h__

/*
 * Number theory.
 *
 * num_len
 * num_upto
 * num_concat
 * is_permutation
 * ifactors
 * GCD
 * LCM
 * totient(!)
 *
 * primes.h:
 * * is_prime
 * * for_each
 */

/* # of decimal digits in 'num'. */
int num_len(int num);

/* A lowest power of 10 which is greater than 'num'. */
int num_upto(int num);

/* n1|n2 */
int num_concat(int n1, int n2);

/* Test if n1 is permutation of n2. */
int is_permutation(int n1, int n2);

/* GCD */
int gcd(int n1, int n2);

void swap(int *i1, int *i2);

/* Integer power */
int ipow(int m, int n);
long lpow(long m, long n);
