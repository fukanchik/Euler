#include <stdio.h>

#define MAX 100
#define UINT unsigned int

static int
digitalsum(UINT a)
{
	int sum = 0;
	for(;a;) {
		UINT digit = a % 10;
		a /= 10u;
		sum += digit;
	}
	return sum;
}

static int
fordigits(int a, int b)
{
	int sum;

	sum = 0;
	for(;a;) {
		int digit = a % 10;
		UINT v = digit * b;
		a /= 10;
		sum += digitalsum(v);
	}

	return sum;
}

int
main(int c, char *v[])
{
	int a, b, i;
	int max;

	printf(">> %d\n", fordigits(13, fordigits(13, fordigits(13, fordigits(13,13)))));

	max = 0;
	for(a=1;a<MAX;a++) {
		for(b=1;b<MAX;b++) {
			UINT sum = 0;
			UINT n=a;
			for(i=1;i<=b;++i) {
				n=fordigits(a, n);
				if(a==13 && b==5) {
					printf("%d %d %d\n", i, n, sum);
				}
				sum += n;
			}
			sum = n;
			if(sum>max) max=sum;
		}
	}
	printf("%d\n", max);
	return 0;
}
