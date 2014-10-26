#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include <euler/assert.h>

/* Greedy */
#define SIZE 100

#define FILENAME "triangle.txt"

static int triangle[SIZE][SIZE];

#define max(x,y) x>y?x:y

static void
read_tri()
{
	int i, j;
	FILE* fi = fopen(FILENAME, "rb");

	memset(triangle, 0, sizeof(triangle));
	for(i=0;i<SIZE;++i) {
		for(j = 0; j < i+1; j++) {
			if(fscanf(fi, "%d", &triangle[i][j]) != 1) FAIL("Can't read number at [%d:%d] from %s", i, j, FILENAME);
		}
	}

	fclose(fi);
}

static void
process()
{
	int i, j;

	for(i=SIZE-1;i>0;--i)
		for(j=0;j<i;++j)
			triangle[i-1][j] += max(triangle[i][j], triangle[i][j+1]);
}

int
main(int argc, char* argv[])
{
	read_tri();
	process();
	printf("%d\n", triangle[0][0]);

	return 0;
}
