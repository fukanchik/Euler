#include <stdio.h>

#define NUM 1000

int
main(int argc, char* argv[])
{
	int sum;
	int i;

	for(sum = 0, i = 1; i < NUM; ++i)
		sum += i * ( ((i % 5) == 0) || ((i % 3) == 0) );

	printf("%d\n", sum);

	return 0;
}
