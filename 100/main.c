#include <stdio.h>

#include <euler/config.h>

#define LD long double
#define MAXNUM 1000000000000ll

static ULL
is_50(ULL blue, ULL red)
{
	return 2000.0 * 
			(LD)blue / ((LD)blue+(LD)red)
			*
			((LD)blue-1.0)/((LD)blue+(LD)red-1.0);
}

int
main(int argc, char *argv[])
{
	ULL i, j;

	printf(ULLFMT "\n", is_50(11, 7));
	printf(ULLFMT "\n", is_50(15, 6));
	printf(ULLFMT "\n", is_50(85, 35));

	for(i=1ll; i < MAXNUM; ++i) {
		j = MAXNUM - i;
		ULL v = is_50(i, j);
		if(v != 1000ll) continue;
		printf(ULLFMT " XX " ULLFMT " = " ULLFMT "\n", i, j, v);
		if(v == 1000ll) break;
	}

	return 0;
}

