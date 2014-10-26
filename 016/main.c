#include <stdio.h>

#include <euler/large.h>

struct large*
two1000()
{
	int i;

	struct large* ret = large_new(1000);
	struct large* two = large_new(5);
	large_set(ret, 1);
	large_set(two, 2);
	for(i=0;i<1000;++i)
	{
		large_mul(ret, two);
	}
	large_free(two);
	return ret;
}

int main(int argc, char* argv[])
{
	struct large* t1000=two1000();
	{
		/*large_print(t1000);*/
		int i;
		int sum = 0;
		for(i=0;i<t1000->capacity; ++i)
		{
			sum+=t1000->buffer[i];
		}
		printf("%d\n", sum);
	}
	large_free(t1000);
	return 0;
}

