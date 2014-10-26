#ifdef __primes_h__
#error "Double inclusion of primes.h!"
#endif
#define __primes_h__

struct prime_list_t
{
	int total;
	int count;
	int *primes;
};

void primes_init_fill( struct prime_list_t * list, int size );
int primes_is_prime( struct prime_list_t * list, int num );

void primes_for_each( struct prime_list_t * list, int (*f)(struct prime_list_t*, int prime, void * arg), void * arg);

void primes_for_each_extra( int start, int end, struct prime_list_t * list, int (*f)(struct prime_list_t*, int position, int prime, void * arg), void * arg);
