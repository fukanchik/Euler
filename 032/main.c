#include <stdio.h>
#include <euler/pandigital.h>

static int
find(int *a, int l, int v)
{
	int i;
	for(i=0;i<l;++i)if(a[i]==v)return 1;
	return 0;
}

int
main(int argc, char *argv[])
{
	int products[100];
	int nprods=0;
	int sum = 0;
	int a;
	int b;

	for(a=1;a<5000;a++)
	{
		for(b=1;b<5000;b++)
		{
			int prod = a * b;
			if(ispandigital(a, b, prod))
			{
				if(!find(products, nprods, prod))
				{
					products[nprods++]=prod;
					sum += prod;
				}
			}
		}
	}
	printf("%d\n", sum);
	return 0;
}

