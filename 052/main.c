#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int
char_cmp(const void* p1, const void*p2)
{
	char *c1=(char*)p1;
	char *c2=(char*)p2;

	return *c2-*c1;
}

int
is_same(int x)
{
	char x1[20];
	char x2[20];
	char x3[20];
	char x4[20];
	char x5[20];
	char x6[20];

	memset(x1, 0, sizeof(x1));
	memset(x2, 0, sizeof(x2));
	memset(x3, 0, sizeof(x3));
	memset(x4, 0, sizeof(x4));
	memset(x5, 0, sizeof(x5));
	memset(x6, 0, sizeof(x6));

	sprintf(x1, "%d", x*1);
	sprintf(x2, "%d", x*2);
	sprintf(x3, "%d", x*3);
	sprintf(x4, "%d", x*4);
	sprintf(x5, "%d", x*5);
	sprintf(x6, "%d", x*6);

	qsort(x1, sizeof(x1), sizeof(char), char_cmp);
	qsort(x2, sizeof(x2), sizeof(char), char_cmp);
	qsort(x3, sizeof(x3), sizeof(char), char_cmp);
	qsort(x4, sizeof(x4), sizeof(char), char_cmp);
	qsort(x5, sizeof(x5), sizeof(char), char_cmp);
	qsort(x6, sizeof(x6), sizeof(char), char_cmp);

	return !strcmp(x1, x2) && !strcmp(x2, x3) && !strcmp(x3, x4) && !strcmp(x4, x5) && !strcmp(x5, x6);
}

int
main(int argc, char* argv[])
{
	int i;

	for(i=1;i<10000000;++i)
	{
		if(is_same(i))
		{
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}

