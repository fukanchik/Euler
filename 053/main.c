#include <stdio.h>
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))

int
C(int n, int r)
{
	int diff = n - r;
	int M = max(r, diff);
	int m = min(r, diff);
	double top;
	int i, j;
	int done=0;

	for(top = 1, i = M+1, j = m; !done && i <= n; ++i)
	{
		top *= i;
		while(top > 1000000)
		{
			if(!j) {done=1;break;}
			top /= j;
			j--;
		}
	}
	return top;
}

int
main(int argc, char* argv[])
{
	int i, j;
	int count = 0;

	for(i=100; i >= 1; --i)
	{
		for(j = 1; j <= i; ++j)
		{
			int v = C(i,j);
			if(v>1000000)count++;
		}
	}
	printf("%d\n", count);
	return 0;
}

