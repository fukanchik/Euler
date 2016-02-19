#ifdef __primes_h__
#error "Double inclusion of primes.h!"
#endif
#define __primes_h__

/* To be merged into number.h */

typedef struct
{
  int total;
  int count;
  int *primes;
} prime_list_t;

void primes_init_fill( prime_list_t * list, int size );
int primes_is_prime( const prime_list_t * const list, int num );

void primes_for_each( prime_list_t * list, int (*f)(const prime_list_t * const, int prime, void * arg), void * arg);
void primes_for_each_simple(prime_list_t * list, int (*f)(const prime_list_t * const , int prime));

void primes_for_each_extra( int start, int end, prime_list_t * list, int (*f)(const prime_list_t* const, int position, int prime, void * arg), void * arg);

/* Euler's totient function (AKA phi). */
int totient(prime_list_t * primes, int num);
