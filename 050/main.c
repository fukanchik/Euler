#include <stdio.h>

#include <euler/primes.h>

static int
isprime(prime_list_t *primes, int num)
{
	int i;

	for(i=primes->count - 1;primes->primes[i] >= num && i>=0;--i)
	{
		if(primes->primes[i]==num) return 1;
	}
	return 0;
}

int
main(int argc, char *argv[])
{
	prime_list_t primes;
	int sum, i;

	primes_init_fill(&primes, 1000000);

	for(sum = 0, i = 0;;i++)
	{
		if(sum + primes.primes[i] > 1000000) break;
		sum += primes.primes[i];
	}
	for(i = 0;i<1000000;)
	{
		if(isprime(&primes, sum))
			break;
		sum -= primes.primes[i];
	}
	printf("%d\n", sum);

	return 0;
}

