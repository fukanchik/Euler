#include <euler/config.h>
#include <stdio.h>

#define COUNT 1000000

static int lens[COUNT];

static u8
next(u8 c)
{
	if (c % 2 == 0) return c / 2;

	return 3 * c + 1;
}

static int
len(u8 n)
{
	if (n < COUNT && lens[n] != 0) return lens[n];

	const u8  orig  = n;
	int count = 0;
	while (n > 1)
	{
		n = next(n);
		if (n < COUNT && lens[n] != 0)
		{
			lens[orig] = lens[n] + count;
			return lens[n] + count;
		}
		count++;
	}

	if (orig < COUNT) lens[orig] = count + 1;

	return count + 1;
}

int
main(int argc, char *argv[])
{
	u8  n   = 13;
	int max = 0;
	int num = -1;
	int i;

	while (n > 1) n = next(n);

	for (i = 1; i < COUNT; ++i)
	{
		int l = len(i);
		if (l > max)
		{
			num = i;
			max = l;
		}
	}

	printf("%d\n", num);

	return 0;
}
