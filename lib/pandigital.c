#include <memory.h>

#include "euler/pandigital.h"

int
ispandigital(int a, int b, int c)
{
	int counts[10];
	int i;

	memset(counts, 0, sizeof(counts));

	while(a)
	{
		int digit = a % 10;
		a /= 10;
		counts[digit]++;
		if(counts[digit] > 1) return 0;
	}
	if(counts[0])return 0;
	while(b)
	{
		int digit = b % 10;
		b /= 10;
		counts[digit]++;
		if(counts[digit] > 1) return 0;
	}
	if(counts[0])return 0;
	while(c)
	{
		int digit = c % 10;
		c /= 10;
		counts[digit]++;
		if(counts[digit] > 1) return 0;
	}
	if(counts[0])return 0;
	for(i=1;i<10;++i)
	{
		if(counts[i] != 1) return 0;
	}
	return 1;
}
