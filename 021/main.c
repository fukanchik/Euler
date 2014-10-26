#include <stdio.h>

static int
sumdivs(int num)
{
	int i;
	int ret=0;

	for(i=1;i<num / 2 + 1;++i)
	{
		if((num%i)==0)
			ret+=i;
	}
	return ret;
}

int
contains(int *arr, int size, int num)
{
	int i;

	for(i=0;i<size;++i)
	{
		if(arr[i]==num)
			return 1;
	}
	return 0;
}

int
main(int argc, char* argv[])
{
	int i;
	int nums[10000];
	int c=0;

	for(i=1;i<10000;++i)
	{
		int s0 = sumdivs(i);
		int s1 = sumdivs(s0);
		if(s1==i && s0 != s1) {
			if(!contains(nums, c, s0))
				nums[c++]=s0;
			if(!contains(nums, c, s1))
				nums[c++]=s1;
		}
	}
	int sum=0;
	for(i=0;i<c;++i)
	{
		sum+=nums[i];
	}
	printf("%d\n", sum);
	return 0;
}
