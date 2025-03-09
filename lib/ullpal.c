#include "euler/config.h"
#include "euler/palindrome.h"

int
ull_is_pal(const u8 candidate, const int base)
{
	u8 num = candidate;
	u8 n = 0;

	while(num)
	{
		n = n * base + num % base;
		num /= base;
	}

	return candidate == n;
}
