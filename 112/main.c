#include <stdio.h>

static int
isincr(int num)
{
	int prev;

	prev=11;
	while(num)
	{
		if(prev < (num % 10))
			return 0;

		prev = num % 10;
		num /= 10;
	}
	return 1;
}

static int
isdecr(int num)
{
	int prev;

	prev=0;
	while(num)
	{
		if(prev > (num % 10))
			return 0;

		prev = num % 10;
		num /= 10;
	}
	return 1;
}

static int
isbouncy(int num)
{
	return !isincr(num) && !isdecr(num);
}

int
main(int argc, char* argv[])
{
	int count=0;
	int i;

	for(i=1;;++i)
	{
		double pc = (double)i / 100.0;
		if(isbouncy(i)) count++;
		
		if(count/pc>=99) { printf("%d\n", i); break;}
	}
	return 0;
}
