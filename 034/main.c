#include <stdio.h>

/* The high limit is 1000000. Consider 9! to get proof. */

static int factorials[]={
	     1, /*0*/
	     1, /*1*/
	     2, /*2*/
	     6, /*3*/
	    24, /*4*/
	   120, /*5*/
	   720, /*6*/
	  5040, /*7*/
	 40320, /*8*/
	362880  /*9*/
	};

static int
isfactsum(int num)
{
	int n=num;
	int sum = 0;

	while(n>=1)
	{
		int digit = n % 10;
		n /= 10;
		sum+=factorials[digit];
	}
	return sum==num;
}

int
main(int argc, char* argv[])
{
	int i;
	int sum = 0;

	for(i=3;i<1000000;++i)
	{
		if(isfactsum(i)) {
			printf("%d\n", i);
			sum += i;
		}
	}
	printf("sum=%d\n", sum);
	return 0;
}
