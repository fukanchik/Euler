#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>

#include <euler/config.h>

/*
	http://blog.functionalfun.net/2008/07/project-euler-problem-15-city-grids-and.html
	http://code.msdn.microsoft.com/projecteuler
*/

struct triangle
{
	ULL *numbers;
	int size;
};

static struct triangle*
pascal_triangle(int size)
{
	struct triangle* ret = (struct triangle*)malloc(sizeof(struct triangle));
	int cs;

	ret->numbers = (ULL*)malloc((size+1)*sizeof(ULL));
	memset(ret->numbers, 0, (size+1)*sizeof(ULL));
	ret->size = size;
	ret->numbers[0]=1;
	ret->numbers[1]=1;
	ret->numbers[2]=0;
	for(cs=2;cs<size;++cs) {
		int i;
		for(i=cs;i>0;--i)
		{
			ret->numbers[i]=ret->numbers[i]+ret->numbers[i-1];
		}
	}

	return ret;
}

#if 0
static void
pascal_triangle_print(struct triangle* t)
{
	int i;

	for(i=0;i<t->size;++i)
	{
		printf(ULLFMT" ", t->numbers[i]);
	}
}
#endif

int
main(int argc, char* argv[])
{
	struct triangle* tr = pascal_triangle(41);

	/*pascal_triangle_print(tr);*/
	printf(ULLFMT"\n", tr->numbers[20]);

	return 0;
}
