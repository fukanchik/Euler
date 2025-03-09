#include <stdio.h>
#include <euler/config.h>

#define MAXNUM 100

static u8
digitalsum(u8 a)
{
	u8 sum = 0;

	for(;a;) {
		u8 digit = a % 10;
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
		u8 v = digit * b;
		a /= 10;
		sum += digitalsum(v);
	}

	return sum;
}

int
main(int argc, char *argv[])
{
	int a, b, i;
	u8 max;

	printf(">> %d\n", fordigits(13, fordigits(13, fordigits(13, fordigits(13,13)))));

	max = 0;
	for(a=1;a<MAXNUM;a++) {
		for(b=1;b<MAXNUM;b++) {
			u8 sum = 0;
			u8 n=a;
			for(i=1;i<=b;++i) {
				n=fordigits(a, n);
				if(a==13 && b==5) {
					printf("%d %llu %llu\n", i, n, sum);
				}
				sum += n;
			}
			sum = n;
			if(sum>max) max=sum;
		}
	}

	printf("%llu\n", max);

	return 0;
}
