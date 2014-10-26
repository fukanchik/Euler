#include <stdio.h>
#include <inttypes.h>

int
main(int c, char *v[])
{
	FILE *fo = fopen("t.txt", "wb");
	long long i;

	for(i=0;i<10000000000llu;++i)
	{
		fprintf(fo, "%"PRId64, i);
	}
	fclose(fo);
	return 0;
}

