#include <euler/config.h>
#include <stdio.h>

static int
isincr(u8 num)
{
	u8 prev = 10;
	while (num)
	{
		u8 digit = num % 10;
		num /= 10;
		if (digit > prev) return 0;
		prev = digit;
	}
	return 1;
}

static int
isdecr(u8 num)
{
	u8 prev = 0;
	while (num)
	{
		u8 digit = num % 10;
		num /= 10;
		if (digit < prev) return 0;
		prev = digit;
	}
	return 1;
}

int
main(int argc, char *argv[])
{
	u8 i;
	u8 nb;

	printf("%d %d %d %d\n", isincr(1234), isincr(12334), isincr(12343),
	       isincr(4321));
	printf("%d %d %d %d\n", isdecr(43210), isdecr(433210), isdecr(433230),
	       isdecr(12340));

	nb = 0;
	for (i = 1; i < 1000000; ++i)
	{
		int ii = isincr(i);
		int id = isdecr(i);
		if (ii || id) nb++;
	}
	printf("nb(10^6)=%llu\n", nb);
	nb = 0;
	for (i = 1; i < 10000000000ull; ++i)
	{
		int ii = isincr(i);
		int id = isdecr(i);
		if (ii || id) nb++;
		if (i % 10000000 == 9999999) printf("%llu\n", i / 10000000);
	}
	printf("nb=%llu\n", nb);
	return 0;
}
