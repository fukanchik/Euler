#include <stdio.h>
#include <math.h>

static int
istriple(int a, int b)
{
	double dc = sqrt( a * a + b * b );
	int c = (int)dc;
	if(dc != c)
		return 0;

	if((a + b + c) == 1000) {
		printf("%d\n", a * b * c);
		return 1;
	}
	return 0;
}

int
main(int argc, char* argv[])
{
	int i,j;

	for(j = 1; j < 1000; ++j)
		for(i = j; i < 1000; ++i)
			if(istriple(i, j))
				return 0;

	return 0;
}
