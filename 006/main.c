#include <stdio.h>

#define NUM 100

static int
sumofsquares(int num)
{
	int sum;
	int i;

	for(i = 1, sum = 0; i <= num; ++i)
		sum += i * i;

	return sum;
}

static int
squareofsums(int num)
{
	int sum;
	int i;

	for(i = 1, sum = 0; i <= num; ++i)
		sum += i;

	return sum * sum;
}

int main(int argc, char* argv[])
{

	printf("%d\n", squareofsums(NUM) - sumofsquares(NUM));

	return 0;
}
