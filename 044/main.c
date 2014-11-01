#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>

#include <euler/config.h>

#define PSIZE 100000

ULL Ps[PSIZE];
ULL Pd[PSIZE];

static ULL
P(ULL n)
{
	return (n * (3ul * n - 1ul)) / 2ul;
}

static int
cmp_int64(const void *n1, const void *n2)
{
	ULL v1 = *(ULL*)n1;
	ULL v2 = *(ULL*)n2;
	if(v1 > v2) return 1;
	if(v1 == v2) return 0;
	if(v1 < v2) return -1;
	return 0;
}

static int
ispent(ULL n)
{
	int *b = bsearch(&n, Pd, PSIZE, sizeof(ULL), cmp_int64);

	if(b!=NULL) return *b;
	return 0;
}

int
main(int argc, char*argv[])
{
	int D = 1;
	int i;

	for(i=0;i<PSIZE;++i)
	{
		Ps[i] = P(i);
	}
	memcpy(Pd, Ps, sizeof(Pd));
	qsort(Pd, PSIZE, sizeof(ULL), cmp_int64);

	for(D=1;D<1150;++D)
	{
		for(i=1;i<PSIZE;++i)
		{
			ULL p1;
			ULL p2;
			if(i+D>PSIZE) continue;
			p1 = Ps[i];
			p2 = Ps[i + D];
			if(ispent(p1+p2) && ispent(p2-p1)) {
				printf("(%d)"ULLFMT" "ULLFMT" D=%d diff="ULLFMT"\n", i, p1, p2, D, p2 - p1);
				return 0;
			}
		}
	}

	return 0;
}
