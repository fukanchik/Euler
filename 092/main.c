#include <stdio.h>

static int
next(int number)
{
	int sum = 0;

	while(number != 0)
	{
		int digit = number % 10;
		number /= 10;
		sum += digit * digit;
	}
	return sum;
}

int
main(int argc, char* argv[])
{
	int count;
	int i;

	for(count=0, i = 1;i<10000000;++i)
	{
		int num = i;
		while(num != 1 && num != 89)
		{
			num = next(num);
		}
		if(num==89)count++;
	}
	printf("%d\n", count);
	return 0;
}
