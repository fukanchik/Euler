#include <stdio.h>

static int
POW(int digit, int power)
{
	int i;
	int ret=1;

	for(i=0;i<power;++i)
	{
		ret *= digit;
	}
	return ret;
}

static int
ispower(int num, int power)
{
	int sum=0;
	int numold=num;

	while(num>=1)
	{
		int digit = num % 10;
		num = num / 10;
		sum += POW(digit, power);
	}
	return sum == numold;
}

int
main(int argc, char* argv[])
{
	int i;
	int sum=0;

	for(i=2;i<1000000;++i) {
		if(ispower(i, 5))
		{
			printf("%d\n", i);
			sum+=i;
		}
	}
	printf("sum=%d\n", sum);
	return 0;
}
