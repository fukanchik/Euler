#include <stdio.h>
#include <euler/config.h>

#define MAXNUM 100

static int
digitalsum(ULL a)
{
	int sum = 0;
	for(;a;) {
		ULL digit = a % 10;
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
		ULL v = digit * b;
		a /= 10;
		sum += digitalsum(v);
	}

	return sum;
}

int
main(int c, char *v[])
{
	int a, b, i;
	ULL max;

	printf(">> %d\n", fordigits(13, fordigits(13, fordigits(13, fordigits(13,13)))));

	max = 0;
	for(a=1;a<MAXNUM;a++) {
		for(b=1;b<MAXNUM;b++) {
			ULL sum = 0;
			ULL n=a;
			for(i=1;i<=b;++i) {
				n=fordigits(a, n);
				if(a==13 && b==5) {
					printf("%d " ULLFMT " " ULLFMT "\n", i, n, sum);
				}
				sum += n;
			}
			sum = n;
			if(sum>max) max=sum;
		}
	}
	printf(ULLFMT "\n", max);
	return 0;
}
