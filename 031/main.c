#include <stdio.h>

#define NUM 200

static int coins[]={1, 2, 5, 10, 20, 50, 100, 200};


static int
f(int num, int start)
{
	int ntries = num / coins[start];
	int count = 0;
	int i, j;

	for(i=0;i<= ntries; ++i)
	{
		int c = num;
		for(j=0;j<i;++j) c -= coins[start];
		if(c==0)
			count++;
		else if(start<7)
			count += f(c, start + 1);
	}
	return count;
}

int
main(int argc, char *argv[])
{
	printf("%d\n", f(NUM, 0));

	return 0;
}

