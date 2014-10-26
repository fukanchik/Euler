#include <stdio.h>
#include <math.h>

#define NUM 1000000

static int primes[NUM];
int nprimes;

static int
fill_sieve(int num)
{
	int half = sqrt(num) + 1;
	int i;

	for(i=0;i<nprimes && primes[i] < half; ++i)
		if((num % primes[i])==0)
			return 0;

	primes[nprimes++] = num;

	return 1;
}

static int
isprime(int num)
{
	int half = sqrt(num) + 1;
	int i;

	for(i=0;i<nprimes && primes[i] < half; ++i)
		if((num % primes[i])==0)
			return 0;

	return 1;
}

static int
nlen(int num)
{
	if(num < 0) return 0;
	if(num < 10) return 1;
	if(num < 100) return 2;
	if(num < 1000) return 3;
	if(num < 10000) return 4;
	if(num < 100000) return 5;
	if(num < 1000000) return 6;

	return 0;
}

int
main(int argc, char* argv[])
{
	int i;
	int count;

	primes[0] = 2;
	nprimes = 1;

	for(i=3;i<NUM;i+=2) fill_sieve(i);

	count = 1;
	for(i=3;i<NUM;i+=2)
	{
		int len = nlen(i);
		int t = len;
		int copy = i;
		int flag=1;
		while(t)
		{
			if(!isprime(copy))
			{
				flag = 0;
				break;
			}
			int digit = copy % 10;
			copy /= 10;
			copy += digit * pow(10, len - 1);
			t--;
		}
		count += flag;
	}
	printf("%d\n", count);

	return 0;
}

