#include <stdio.h>

#define min(x,y) (x<y?x:y)

static int
is_curious(int num, int den)
{
	int dn0 = num % 10;
	int dn1 = num / 10;
	int dd0 = den % 10;
	int dd1 = den / 10;

	double d0 = (double)num / (double)den;

	if(dn0==dd1&&dd0!=0&&(double)dn1/(double)dd0==d0) return 1;
	if(dn1==dd0&&dd1!=0&&(double)dn0/(double)dd1==d0) return 1;

	return 0;
}

static int
least_common_term(int num, int den)
{
	int f = min(num, den);
	int i;

	for(i = f / 2 - 1;i >= 2; --i)
	{
		if(num % i == 0 && den % i == 0)
		{
			num /= i;
			den /=i;
		}
	}
	return den;
}

int
main(int argc, char* argv[])
{
	int i, j;
	int num, den;

	for(num=1, den=1,i=1;i<100;++i)
		for(j=i+1;j<100;++j)
			if(is_curious(i, j))
			{
				num *= i;
				den *= j;
			}
	printf("%d\n", least_common_term(num, den));
	return 0;
}
