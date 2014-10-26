#include <stdio.h>

int
num_factors(int num)
{
	int i;
	int ret=0;

	for(i=2;num>1;++i)
	{
		int add=1;
		while(num%i==0) {
			ret+=add;
			add=0;
			num/=i;
			if(ret>5)
				return -1;
		}
	}
	return ret;
}

int
main(int argc, char* argv[])
{
	int i;

	for(i=100000;i<200000;++i) {
		int n0=num_factors(i);
		int n1=num_factors(i+1);
		int n2=num_factors(i+2);
		int n3=num_factors(i+3);

		if(n0==4 && n1==4 && n2==4 && n3==4) {
			printf("%d\n", i);
		}
	}
	return 0;
}

