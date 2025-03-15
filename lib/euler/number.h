#ifdef __number_h__
#error "Double inclusion of number.h!"
#endif
#define __number_h__

#include <stdbool.h>
#include <euler/config.h>

#define DIGITS_U8 20

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

bool is_square(u8 num);

/* Split number into digits. `digits' array should be DIGITS_U8 length. */
void num_to_digits(u8 num, int *digits, int *dlen);

/* GCD */
int gcd(int n1, int n2);

void swap(int *i1, int *i2);

/* Integer power */
int ipow(int m, int n);
long lpow(long m, long n);
