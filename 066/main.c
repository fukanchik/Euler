#include <euler/assert.h>
#include <euler/number.h>
#include <euler/primes.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#if 0
static prime_list_t primes;
u8                find_solution(u8 D, u8 distance);

u8
acc(ifactors_map_t *ifs)
{
	u8 ret = 1;

	for (u8 i = 0; i < ifs->nfactors; ++i)
	{
		u8 prime = ifs->primes[i];
		u8 power = ifs->powers[i];

		if (power % 2) return 0;

		ret *= lpow(prime, power / 2);
	}

	return ret;
}

u8
find_solution(u8 D, u8 distance)
{
	for (u8 y = 1; y < distance; ++y)
	{
		u8           y2  = 1 + D * y * y;
		ifactors_map_t ifs = ifactors(&primes, y2);
		u8           x   = acc(&ifs);
		ifactors_map_free(&ifs);
		if (x != 0)
		{
			printf("D=%llu, x=%llu, y=%llu\n", D, x, y);
			return x;
		}
	}
	return 9;
}
#endif


typedef struct
{
	u8 *ptr;
	u8 count;
} u8_array;

void
append(u8_array *arr, u8 num)
{
	u8 new_size = sizeof(u8) * (arr->count + 1);
	u8*ptr = realloc(arr->ptr, new_size);
	if (!ptr)
		FAIL("Can' allocate %llu", new_size);
	ptr[arr->count] = num;
	arr->ptr = ptr;
	arr->count = arr->count + 1;
}

u8_array
prefill(u8 D)
{
	u8_array ret = {0,0};
	u8 next = 0;

	for (u8 i = 2; i < 8ul*1000ul*1000ul*1000ul;++i)
	{
		u8 n = i*i-1;
		if (n % D == 0)
		{
			if (i == next)
				break;
			append(&ret, i);
			if (next == 0)
				next = i + D;
		}
	}
	return ret;
}

u8
find_solution3(u8 D)
{
	u8 ret = 0;
	u8_array nums = prefill(D);
	bool done;

	for(u8 i=2;i<8ul*1000ul*1000ul*1000ul*1000ul;++i)
	{
		done = false;
		for(u8 j=0; j < nums.count;++j)
		{
			u8 n = nums.ptr[j];
			u8 v = (n*n-1) / D;
			if (is_square(v))
			{
				ret = n;
				done = true;
				break;
			}
		}

		if (done)
			break;
		for(u8 j=0;j<nums.count;++j)
		{
			nums.ptr[j] += D;
		}
	}
	if (!done)
	{
		FAIL("%llu: nothing found", D);
	}
	return ret;
}

u8
find_solution2(u8 D)
{
	for (u8 x = 2;;++x)
	{
		u8 v1 = x*x - 1u;
		if (v1 % D) continue;
		u8 v2 = v1 / D;
		if (is_square(v2))
			return x;
	}
	return 0;
}

int
main(int argc, char *argv[])
{
	u8 max_pos = 0;
	u8 max_sol     = 0;
	u8 next_square = 2;

	for (u8 i = 2; i <= 1000; ++i)
	{
		if (i == next_square * next_square)
		{
			next_square++;
			continue;
		}

		u8 sol = find_solution3(i);
		if (sol > max_sol)
		{
			max_pos = i;
			max_sol = sol;
		}

		printf("%llu: %llu (%llu at %llu)\n", i, sol, max_sol, max_pos);
		fflush(stdout);
	}

	printf("max=%llu pos=%llu\n", max_sol, max_pos);

	return 0;
}
