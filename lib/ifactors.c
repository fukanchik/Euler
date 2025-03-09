#include <stddef.h>
#include <stdlib.h>
#include <euler/assert.h>
#include <euler/primes.h>

/* How many times a prime divides a number */
int
prime_root(long *num, long prime)
{
	int ret = 0;

	if (prime == 1) return *num;

	while (*num % prime == 0)
	{
		ret += 1;
		*num /= prime;
	}

	return ret;
}

void ifactors_map_insert(ifactors_map_t *map, int prime, int power)
{
	map->nfactors++;
	map->primes = realloc(map->primes, sizeof(int)*map->nfactors);
	map->powers = realloc(map->powers, sizeof(int)*map->nfactors);
	map->primes[map->nfactors-1] = prime;
	map->powers[map->nfactors-1] = power;
}

void
ifactors_map_free(ifactors_map_t *map)
{
	free(map->primes);
	free(map->powers);
	map->primes = NULL;
	map->powers = NULL;
	map->nfactors = 0;
}

ifactors_map_t
ifactors(prime_list_t *primes, long num)
{
	ifactors_map_t ret = {NULL, NULL, 0};


	for(int current_prime_idx = 0; num != 1; current_prime_idx++)
	{
		if (current_prime_idx >= primes->count)
			FAIL("Not enough primes for %ld", num);
		const int current_prime = primes->primes[current_prime_idx];
		if (current_prime > num)
			break;

		const int current_power = prime_root(&num, current_prime);

		if (current_power > 0)
		{
			ifactors_map_insert(&ret, current_prime, current_power);
		}
	}

	return ret;
}
