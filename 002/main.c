#include <stdio.h>

int
main(int argc, char* argv[])
{
	int sum = 0;
	int f0 = 1;
	int f1 = 1;

	for ( sum = 0, f0 = 1, f1 = 1; f1 < 4000000; )
	{
		int fc = f0 + f1;

		if( (f1 % 2) == 0 )
			sum += f1;

		f0 = f1;
		f1 = fc;
	}
	printf("%d\n", sum);

	return 0;
}
