#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <process.h>
#endif
#include <malloc.h>
#include <math.h>

#include <euler/config.h>
#include <euler/primes.h>

static void
primes_init( prime_list_t * list, int size )
{
	list->total = size;
	list->count = 0;
	list->primes = malloc(sizeof(int) * size);
}

void
primes_free(prime_list_t * list)
{
  if(list)
    {
      memset(list->primes, 0, sizeof(int) * list->total);
      free(list->primes);
      list->primes = NULL;
    }
}

void
primes_for_each( prime_list_t * list, int (*f)(const prime_list_t* const, int prime, void * arg), void * arg)
{
	int i;

	for(i = 0; i < list->count; ++i)
	{
	  if(f(list, list->primes[i], arg))
			break;
	}
}

void
primes_for_each_simple(prime_list_t * list, int (*f)(const prime_list_t* const, int prime) )
{
	int i;

	for(i = 0; i < list->count; ++i)
	{
	  if(f(list, list->primes[i]))
			break;
	}
}


void
primes_for_each_extra( int start, int end, prime_list_t * list, int (*f)(const prime_list_t* const, int position, int prime, void * arg), void * arg)
{
	int i;

	for(i = start; i < MIN(end, list->count); ++i)
	{
	  if(f(list, i, list->primes[i], arg))
			break;
	}
}

static void
primes_add( prime_list_t * list, int prime )
{
	if(list->total == list->count)
	{
		fprintf(stderr, "Primes list is full!\n");
		abort();
	}
	list->primes[list->count++] = prime;
}

static int
primes_add_sieve( prime_list_t * list, int num)
{
	int half = sqrt(num) + 1;
	int i;

	for(i=0;i < list->count && list->primes[i] < half; ++i)
		if((num % list->primes[i])==0)
			return 0;

	primes_add( list, num );

	return 1;
}

void
primes_init_fill( prime_list_t * list, int size )
{
	int i;

	primes_init( list, size / 2 );
	primes_add( list, 2 );

	for(i = 3; i < size; ++i)
		primes_add_sieve( list, i );
}


int
primes_is_prime( const prime_list_t * const list, int num )
{
  /* TODO: if num <= list->primes[max], then do binary search in the list. */
	int half = sqrt(num) + 1;
	int i;

	if(num==1) return 0;
	for(i=0;i < list->count && list->primes[i] < half; ++i)
		if((num % list->primes[i])==0)
			return 0;

	return 1;
}

