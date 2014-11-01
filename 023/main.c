#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

static int
sum_of_divisors(const int num)
{
	int sum;
	int i;

	for(sum = 0, i = 1; i <= num / 2; ++i)
	{
		if(num % i == 0) sum += i;
	}
	return sum;
}

static int
is_perfect(const int num)
{
	return num == sum_of_divisors(num);
}

static int
is_abundant(const int num)
{
	return sum_of_divisors(num) > num;
}

static int
contains(int *a, int c, int n)
{
	int mid;
	int b = 0;
	int u = c - 1;

	if(c == 0)return 0;

	while(b <= u) {
		mid = b + (u - b) / 2;
		if(a[mid] == n)
			return 1;
		if(a[mid] < n)
		{
			b = mid + 1;
		} else {
			u = mid - 1;
		}
	}
	return 0;
}

static int nums[100000];
static int ncount=0;
static int sums[200000];
static int nsums=0;
static int total=0;

static int
int_cmp(const void*a, const void*b)
{
	const int*v1=(int*)a;
	const int*v2=(int*)b;

	return *v1 - *v2;
}

int
main(int argc, char* argv[])
{
	int i, j;

	assert(sum_of_divisors(28)==28);
	assert(is_perfect(28));
	assert(is_abundant(12));

	for(i=1;i <= 28123; i++)
	{
		if(is_abundant(i))
		{
			nums[ncount++]=i;
		}
	}

	memset(sums, 0, sizeof(sums));
	nsums=0;

	for(i=0;i<ncount;++i)
	{
		for(j=0;j<ncount;++j)
		{
			int sum = nums[i] + nums[j];
			if(!contains(sums, nsums , sum))
			{
				sums[nsums++]=sum;
				qsort(sums, nsums, sizeof(int), int_cmp);
			}
		}
 	}

	for(i=1;i<=28123;++i)
	{
		if(!contains(sums, nsums, i))
			total+=i;
	}
	printf("Total is %d\n", total);
	return 0;
}
