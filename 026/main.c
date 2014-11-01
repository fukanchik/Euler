#include <stdio.h>
#include <math.h>
#include <string.h>

static int
nmultiplier(int num)
{
	if(num<0)return 0;
	if(num<10)return 1;
	if(num<100)return 2;
	if(num<1000)return 3;
	return 0;
}

static int
pow10(int n)
{
	if(n==0)return 1;
	if(n==1)return 10;
	if(n==2)return 100;
	if(n==3) return 1000;
	return 0;
}

static int
find(int* a, int l, int n){
	int i;

	for(i=0;i<l;++i)
	{
		if(a[i]==n)return 1;
	}
	return 0;
}

int
main(int argc, char* argv[])
{
	int div;
	int max=0;
	int val = -1;

	for(div=1;div<1000;++div) {
		int i;
		int digits[1000];
		int ndigits;
		int num = 1;
		int nn = nmultiplier(div);
		memset(digits, 0, sizeof(digits));
		ndigits=0;

		for(i=0;i<1000;++i)
		{
			num *= pow10(nn);
		
			num %= div;

			if(!find(digits, ndigits, num))
				digits[ndigits++]=num;
		}
		if(ndigits>max)
		{
			max = ndigits;
			val=div;
		}
	}
	printf("%d\n", val);
	return 0;
}

