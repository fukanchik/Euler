#ifdef __primes_h__
#error "Double inclusion of primes.h!"
#endif
#define __primes_h__

#include <stdbool.h>
#include <euler/config.h>

/* To be merged into number.h */

typedef struct
{
  u8 total;
  u8 count;
  u8 *primes;
} prime_list_t;

void primes_init_fill(prime_list_t *list, u8 size);
void primes_free(prime_list_t *list);

void primes_dump(prime_list_t *primes, const char *fname);
void primes_load(prime_list_t *primes, const char *fname);

bool primes_is_prime(const prime_list_t * const list, u8 num);

void primes_for_each( prime_list_t * list, bool (*f)(const prime_list_t * const, u8 prime, void * arg), void * arg);
void primes_for_each_simple(prime_list_t * list, bool (*f)(const prime_list_t * const , u8 prime));
void primes_for_each_extra(u8 start, u8 end, prime_list_t * list, bool (*f)(const prime_list_t* const, u8 position, u8 prime, void * arg), void * arg);

/* Euler's totient function (AKA phi). */
int totient(prime_list_t * primes, int num);

/* How many times a prime divides a number */
u8 prime_root(u8 *num, u8 prime);

typedef struct
{
	u8 *primes;
	u8 *powers;
	int nfactors;
} ifactors_map_t;

void ifactors_map_insert(ifactors_map_t *map, u8 prime, u8 power);
void ifactors_map_free(ifactors_map_t *map);

/* Find factors for a number */
ifactors_map_t ifactors(prime_list_t * primes, u8 num);
