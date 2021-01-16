#include <stdio.h>
#include <string.h>

#include <euler/palindrome.h>
/*
 * Exhaustive search as search space is tiny.
 */
int
main(int argc, char* argv[])
{
	int i, j;
	int maxpal;

	for(maxpal = 0, i = 100; i <= 999; ++i)
	{
		for(j=999; j>=100;--j) {
			int num=i*j;
			if(ispal10(num))
			{
				if(num>maxpal) {
					maxpal=num;
				}
			}
		}
	}

	if(maxpal != 0)
		printf("%d\n", maxpal);

	return 0;
}
