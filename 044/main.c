#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>

#include <euler/config.h>

#define PSIZE 100000

u8 Ps[PSIZE];
u8 Pd[PSIZE];

static u8
P(u8 n)
{
	return (n * (3ul * n - 1ul)) / 2ul;
}

static int
cmp_int64(const void *n1, const void *n2)
{
	u8 v1 = *(u8*)n1;
	u8 v2 = *(u8*)n2;

	if(v1 > v2) return 1;
	if(v1 == v2) return 0;
	if(v1 < v2) return -1;

	return 0;
}

static int
ispent(u8 n)
{
	int *b = bsearch(&n, Pd, PSIZE, sizeof(u8), cmp_int64);

	if(b != NULL)
		return *b;

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
	qsort(Pd, PSIZE, sizeof(u8), cmp_int64);

	for(D=1;D<1150;++D)
	{
		for(i=1;i<PSIZE;++i)
		{
			u8 p1;
			u8 p2;

			if(i+D>PSIZE) continue;

			p1 = Ps[i];
			p2 = Ps[i + D];

			if(ispent(p1+p2) && ispent(p2-p1)) {
				printf("(%d)%llu %llu D=%d diff=%llu\n", i, p1, p2, D, p2 - p1);
				return 0;
			}
		}
	}

	return 0;
}
