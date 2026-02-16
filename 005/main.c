#include <stdio.h>

#include <euler/config.h>
#include <euler/primes.h>

int
main(int argc, char *argv[])
{
	prime_list_t primes;
	primes_init_fill(&primes, 21);
	u8 counts[21] = {0};

	for (u8 i = 2; i <= 20; ++i)
	{
		ifactors_map_t ifact = ifactors(&primes, i);
		for (u8 j = 0; j < ifact.nfactors; ++j)
		{
			const u8 prime = ifact.primes[j];
			const u8 pow   = ifact.powers[j];

			counts[prime] = MAX(counts[prime], pow);
		}
	}

	u8 res = 1;
	for (int i = 0; i < 21; ++i)
	{
		if (counts[i] == 0) continue;
		for (int j = 0; j < counts[i]; ++j) res *= i;
	}
	printf("%llu\n", res);

	return 0;
}
