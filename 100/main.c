#include <stdio.h>

#include <euler/config.h>

#define LD long double
#define MAXNUM 1000000000000ll

static u8
is_50(u8 blue, u8 red)
{
	return 2000.0 *
			(LD)blue / ((LD)blue+(LD)red)
			*
			((LD)blue-1.0)/((LD)blue+(LD)red-1.0);
}

int
main(int argc, char *argv[])
{
	u8 i, j;

	printf("%llu\n", is_50(11, 7));
	printf("%llu\n", is_50(15, 6));
	printf("%llu\n", is_50(85, 35));

	for(i=1ll; i < MAXNUM; ++i) {
		j = MAXNUM - i;
		u8 v = is_50(i, j);
		if(v != 1000ll) continue;
		printf("%llu XX %llu = %llu\n", i, j, v);
		if(v == 1000ll) break;
	}

	return 0;
}
