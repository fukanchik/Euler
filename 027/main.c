#include <stdio.h>

#include <euler/primes.h>

static int
number_of_primes( struct prime_list_t * primes, int a, int b)
{
	int n;

	for(n=0;;n++)
	{
		int quad = n * n + a * n + b;
		if(quad<0) return 0;

		if(!primes_is_prime( primes, quad))
			return n + 1;
	}
}

int
main(int argc, char* argv[])
{
	struct prime_list_t primes;
	int a, b;
	int ca, cb, max;

	primes_init_fill( &primes, 1000 );

	max = 0;
	ca = cb = 0;
	for(a = -999; a < 1000; ++a)
	{
		for(b = -999; b < 1000; ++b)
		{
			int num = number_of_primes(&primes, a, b);
			if(num > max)
			{
				max = num;
				ca = a;
				cb = b;
			}
		}
	}
	printf("%d\n", ca * cb);

	return 0;
}

