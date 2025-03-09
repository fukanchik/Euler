#include <stdio.h>
#include <math.h>

#include <euler/config.h>

#define SIZE 2000000

static u8 primes[SIZE];
static int current;

static int
isprime(int num)
{
	int half = sqrt(num) + 1;
	int i;

	for(i = 0; i < current && primes[i] < half; ++i)
		if((num % primes[i]) == 0)
			return 0;

	primes[current++] = num;

	return 1;
}

int
main(int argc, char* argv[])
{
	u8 sum;
	int i;

	primes[0]=2;
	current=1;

	for( sum = 2, i = 3; i < SIZE; i += 2)
		sum += i * isprime(i);

	printf("%llu\n", sum);

	return 0;
}
