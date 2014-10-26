#include <stdio.h>

#define MAXNUM 1000000

static int factorials[]={1,1,2,6,24,120,720,5040,40320,362880};

static int
nonreplen(int num)
{
	int count = 0;

	while(num != 0 && num != 169 && num != 872 && num != 871)
	{
		int sum = 0;
		while(num != 0)
		{
			int digit = num % 10;
			num /= 10;

			sum += factorials[digit];
		}
		num = sum;
		count++;
		if(count > 58) break;
	}
	if(num==169) count+=3;
	else if(num==871) count += 2;
	else if(num==872) count += 2;
	return count;
}

int
main(int argc, char *argv[])
{
	int num;
	int count;

	for(count = 0, num = 0; num < MAXNUM; ++num)
	{
		if(nonreplen(num) == 60) count++;
	}
	printf("%d\n", count);

	return 0;
}

