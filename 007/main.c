#include <stdio.h>

#define SIZE 10001
#define MAXNUM 1000000

int sito[SIZE];
int current;

int main(int argc, char* argv[])
{
	int i, j;

	sito[0] = 2;
	current = 1;

	for(i = 3; i <= MAXNUM; i += 2)
	{
		int nnn = 1;
		for(j = 0; j < current; ++j) {
			if((i % sito[j]) == 0) {
				nnn = 0;
				break;
			}
		}
		if(nnn) {
			sito[current] = i;
			current++;
			if(current >= SIZE) {
				break;
			}
		}
	}

	printf("%d\n", sito[SIZE-1]);

	return 0;
}

