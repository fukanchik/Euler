#include <stdio.h>

#include <euler/pandigital.h>

static int
multiplier(int v)
{
	if(v<10)
		return 10;
	if(v<100)
		return 100;
	if(v<1000)
		return 1000;
	if(v<10000)
		return 10000;
	if(v<100000)
		return 100000;
	if(v<1000000)
		return 1000000;
	printf("err\n");
	return -1;
}

int
main(int argc, char *argv[])
{
	int maxpandigital = 0;
	int i;

	for(i=0; i < 10000; ++i)
	{
		int pow2 = multiplier(i*2);

		if(ispandigital(i*1, i*2, 0))
		{
			int pd = i*pow2 + i*2;
			if(maxpandigital<pd)
				maxpandigital = pd;
		}
	}
	printf("%d\n", maxpandigital);
	
	return 0;
}

