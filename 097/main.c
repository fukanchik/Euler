/* Wrong with windows, corrent in linux.
BUG in gcc on windows.
*/
#include <stdio.h>
#include <euler/config.h>

#define NUM 7830457

static ULL
two7830457()
{
	ULL ret = 1ULL;
	int i;

	for(i = 0; i < NUM; ++i) {
		ret = ret * 2ULL;
		ret = ret % 10000000000ULL;
	}

	ret = ret * 28433ll;
	ret = ret % 10000000000ULL;
	ret = ret + 1ll;
	ret = ret % 10000000000ULL;

	return ret;
}

int
main(int argc, char* argv[])
{
	ULL two=two7830457();
	printf(ULLFMT "\n", two);

	return 0;
}
