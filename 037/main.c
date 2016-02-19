#include <stdio.h>

#include <euler/primes.h>
#include <euler/reverse.h>

static int sum = 0;
static int count=0;

static int
check_trunc(const prime_list_t * const list, int prime )
{
	int primeo = prime;
	int rev = reverse(prime);

	if(prime==2||prime==3||prime==5||prime==7)return 0;
	while(1)
	{
		prime /= 10;
		if(prime==0)break;
		if(!primes_is_prime(list, prime)) return 0;
	}
	while(1)
	{
		rev /= 10;
		if(rev==0)break;
		if(!primes_is_prime(list, reverse(rev))) return 0;
	}
	sum += primeo;
	count++;
	return count==11;
}

int
main(int argc, char *argv[])
{
	prime_list_t primes;

	primes_init_fill(&primes, 1000000);

	primes_for_each_simple(&primes, check_trunc);

	printf("%d\n", sum);

	return 0;
}

