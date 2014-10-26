#include <stdio.h>
#include <memory.h>
#include <time.h>

#include <euler/large.h>

static struct large* nums[100 * 100];
static int ncount;

int
main(int argc, char* argv[])
{
	time_t start, end;
	int a, b;
	int i, j;
	int count;

	memset(nums, 0, sizeof(nums));
	ncount = 0;

	for(a = 2; a <= 100; ++a)
	{
		start = time(NULL);
		for(b = 2; b <= 100; ++b)
		{
			struct large* num = large_pow(a, b);
			nums[ncount++] = num;
		}
		end = time(NULL);
		printf("%d/%.01f\n", a, difftime(end, start));
	}
	for(i = 0; i < 100 * 100; ++i)
	{
		for(j = i + 1; j < 100 * 100; ++j)
		{
			if(nums[i]==NULL||nums[j]==NULL) continue;
			if(large_compare(nums[i], nums[j])==0)
			{
				large_free(nums[j]);
				nums[j] = NULL;
			}
		}
	}
	count=0;
	for(i = 0; i < 100 * 100; ++i)
	{
		if(nums[i]!=NULL)count++;
	}
	printf("%d\n", count);
	return 0;
}
