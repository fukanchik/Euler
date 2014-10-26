#include <stdio.h>

#define NUM 20

int
main(int argc, char* argv[])
{
	int i, j;
	int nnn = 1;
	int mul = 0;

	for(j = 1; nnn; ++j) {
		nnn = 0;
		for(i = 1; i <= NUM; ++i)
		{
			if(j % i)
			{
				nnn = 1;
				break;
			}
		}
		if(!nnn) mul = j;
	}

	printf("%d\n", mul);

	return 0;
}
