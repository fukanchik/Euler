#include <stdio.h>
#include <string.h>

#include <euler/primes.h>

static int
ispandigital(int num)
{
	unsigned int counts[10];
	int i;

	memset(counts, 0, sizeof(counts));

	while(num)
	{
		int digit = num % 10;
		num /= 10;
		counts[digit]++;
		if(counts[digit] > 1) return 0;
	}
	if(counts[0])return 0;

	for(i=1;i<10;++i)
	{
		int j;
		if(counts[i] == 1) continue;

		for(j=i;j<10;++j)
		{
			if(counts[j]!=0)return 0;
		}
		break;
	}

	return 1;
}

int
main(int argc, char *argv[])
{
	prime_list_t primes;
	int max_digits;
	int i;

	/* 9+8+7+6+5+4+3+2+1 is divisable by 3. This means exclude 9. */
	/* 8+7+6+5+4+3+2+1 is divisable by 3. This means exclude 8.*/
	max_digits=10000000;/*<< Places for 1, 2, 3, 4, 5, 6, 7 */
	primes_init_fill( &primes, max_digits );
	printf("Filled\n");

	for(i=primes.count - 1; i>=0; --i)
	{
		if(ispandigital(primes.primes[i]))
		{
			printf("%llu\n", primes.primes[i]);
			break;
		}
	}

	return 0;
}
