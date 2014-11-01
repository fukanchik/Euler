#include <stdio.h>

#include <euler/config.h>

static ULL
next(ULL c)
{
	if(c % 2 == 0)
		return c / 2;

	return 3 * c + 1;
}

static int len(ULL n)
{
	int count = 0;
	while(n > 1) {
		n = next(n);
		count++;
	}
	return count+1;
}

int
main(int argc, char* argv[])
{
	ULL n = 13;
	int max=0;
	int num;
	int i;

	while(n > 1)
		n = next(n);

	for(i = 1; i < 1000000; ++i)
	{
		int l = len(i);
		if(l > max){num = i; max = l;}
	}

	printf("%d\n", num);

	return 0;
}

