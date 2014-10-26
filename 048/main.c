#include <stdio.h>

#include <euler/large.h>

#define START 11
#define LEN 20

struct large*
mult(int n)
{
	int i;
	struct large* ret = large_new(LEN);
	large_set(ret, 1);
	{
		struct large* tmp = large_new(LEN);
		large_set(tmp, n);
		for(i=1;i<=n;++i)
		{
			int k;

			large_mul(ret, tmp);
			for(k=START;k<LEN;k++)
			{
				ret->buffer[k]=0;
			}
		}
		large_free(tmp);
	}
	return ret;
}

int
main(int argc, char* argv[])
{
	struct large* result = large_new(LEN);
	int i, j;

	for(i=1;i<=1000;++i)
	{
		struct large* m = mult(i);
		large_add(result, m);
		large_free(m);
		for(j=START;j<LEN;++j)
		{
			result->buffer[j]=0;
		}
	}
	printf("Result: ");
	large_print(result);
	large_free(result);
	printf("\n");
	return 0;
}
