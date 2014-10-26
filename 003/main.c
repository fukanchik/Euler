#include <stdio.h>

int
main(int argc, char* argv[])
{
	long long NUM = 600851475143ll;
	long long max;
	long long i;

	for( max = 0ll, i = 2ll; i <= NUM; ++i) {
		if(NUM % i)
			continue;
		NUM = NUM / i;
		if(i > max)
			max = i;
	}

	printf("%lld\n", max);

	return 0;
}
