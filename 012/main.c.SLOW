#include <stdio.h>

#include <euler/config.h>

static int
numdivs(ULL num)
{
	int count=0;
	ULL divisor;

	divisor=1;
	while(num>=divisor)
	{
		if(num%divisor==0)
		{
			count++;
		}
		divisor++;
	}
	return count;
}

int
main(int argc, char* argv[])
{
	ULL i;
	ULL tri;
	int nd, max=0;

	for(i=11000;i<1000000;++i)
	{
		tri=(i * (i + 1))/2l;
		if(i%1000==998)printf(ULLFMT" => "ULLFMT" ", i, tri);
		nd=numdivs(tri);
		if(nd>max)max=nd;
		if(i%1000==998)printf(" ... %d\n", nd);
		if(nd>500) {
			printf(ULLFMT"\n", tri);
			return 0;
		}
	}
	printf("Nothing: %d\n", max);
	return 0;
}
