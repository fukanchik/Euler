#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define XMAX 1000
#define YMAX XMAX

static int
array[XMAX][YMAX];

static void
init()
{
	int i, j;

	for(i=0;i<XMAX;++i)
		for(j=0;j<YMAX;++j)
			array[i][j] = -1;
}

static int
nrects(int x, int y)
{
	int ret = 0;
	int i, j;

	for(i=0;i<x;++i) {
		for(j=0;j<y;++j) {
			ret += (x-i) * (y-j);
		}
	}
	return ret;
}

static int
nrects2(int x, int y)
{
	int ret;

	if(array[x][y] != -1)
		return array[x][y];

	ret = nrects(x, y);
	array[x][y]=ret;
	array[y][x]=ret;
	return ret;
}

int
main(int argc, char *argv[])
{
	int square=0;
	int delta = XMAX*YMAX*10;
	int i, j;
	int nr = nrects(3,2);
	if(nr != 18) {
		fprintf(stderr, "nrects(3,2)=%d\n", nr);
		return -1;
	}

	init();

	for(i=1;i<XMAX;++i) {
		for(j=0;j<YMAX;++j) {
			int ldelta;
			nr = nrects2(i,j);
//			printf("%d:%d %d\n", i, j, nr);
			ldelta = abs(2000000-nr);
			if(delta > ldelta) {
				delta = ldelta;
				square = i * j;
			}
		}
		printf(">>%d\n", i);
	}
	printf("DELTA=%d SQ=%d\n", delta, square);
	return 0;
}

