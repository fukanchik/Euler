#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <process.h>
#endif

#include <euler/reverse.h>

static int
nlen(int num)
{
	if(num<0) abort();
	if(num<10)return 1;
	if(num<100)return 2;
	if(num<1000)return 3;
	if(num<10000)return 4;
	if(num<100000)return 5;
	if(num<1000000)return 6;
	abort();
}

static int pos[]={1, 10, 100, 1000, 10000, 100000, 1000000};

static int digit(int num, int n)
{
	int ret;

	while(n)
	{
		num /= 10;
		n--;
	}
	ret = num % 10;
	return ret;
}

int
main(int argc, char *argv[])
{
	int num = 1;
	int len;
	int npos = 0;
	int total=1;
	int mul = 1;


	for(num = 1; num <= 1000000; ++num)
	{
		len = nlen(num);
		if(total + len > pos[npos])
		{
			int v = total + len - pos[npos];
			mul *= digit(reverse(num), len - v);
			npos++;
			if(npos==7) break;
		}
		total += len;
	}
	printf("%d\n", mul);

	return 0;
}

