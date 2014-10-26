#include <stdio.h>

#include <euler/config.h>

#define START 1

int
main(int argc, char* argv[])
{
	int add=2;
	ULL sum = START;
	ULL num = START;
	int i, j;

	for(j=0;j<500;++j) {
		for(i=0;i<4;++i)
		{
			num += add;
			sum+=num;
		}
		add += 2;
	}
	printf(ULLFMT"\n", sum);
	return 0;
}
