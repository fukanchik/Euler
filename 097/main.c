#include <euler/config.h>
#include <stdio.h>

#define NUM 7830457

static u8
two7830457(void)
{
	u8  ret = 1ULL;
	int i;

	for (i = 0; i < NUM; ++i)
	{
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
main(int argc, char *argv[])
{
	u8 two = two7830457();
	printf("%llu\n", two);

	return 0;
}
