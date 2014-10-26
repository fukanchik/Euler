#include <stdio.h>
#include <math.h>

#include <euler/primes.h>

#define UPPER 100000

struct prime_list_t primes;

int
is_goldbach_other(int num, int *out_prime, int *out_square)
{
	int i;
	for(i=num-1;i > 1;i--) {
		int prime_candidate, remains, sqroot;

		if(!primes_is_prime(&primes, i)) {
			continue;
		}
		prime_candidate=i;
		remains = num - prime_candidate;
		if((remains & 1) == 1) {
			continue;
		}
		remains /= 2;
		for(sqroot=1;sqroot*sqroot <= remains;++sqroot) {
			if(sqroot*sqroot == remains) break;
		}
		if(sqroot*sqroot != remains) {
			continue;
		}
		*out_prime=prime_candidate;
		*out_square=sqroot;
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int i;

	primes_init_fill( &primes, UPPER);
	for(i=9;i<UPPER;i+=2)
	{
		int prime, square;

		if(primes_is_prime(&primes, i)) continue;
		if(!is_goldbach_other(i, &prime, &square)) {
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}

