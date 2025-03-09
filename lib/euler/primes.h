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
void primes_free(prime_list_t *list);

void primes_dump(prime_list_t *primes, const char *fname);
void primes_load(prime_list_t *primes, const char *fname);

int primes_is_prime( const prime_list_t * const list, int num );

void primes_for_each( prime_list_t * list, int (*f)(const prime_list_t * const, int prime, void * arg), void * arg);
void primes_for_each_simple(prime_list_t * list, int (*f)(const prime_list_t * const , int prime));

void primes_for_each_extra( int start, int end, prime_list_t * list, int (*f)(const prime_list_t* const, int position, int prime, void * arg), void * arg);

/* Euler's totient function (AKA phi). */
int totient(prime_list_t * primes, int num);

/* How many times a prime divides a number */
int prime_root(long *num, long prime);

typedef struct
{
	int *primes;
	int *powers;
	int nfactors;
} ifactors_map_t;

void ifactors_map_insert(ifactors_map_t *map, int prime, int power);
void ifactors_map_free(ifactors_map_t *map);

/* Find factors for a number */
ifactors_map_t ifactors(prime_list_t * primes, long num);
