#include "euler/config.h"
#include "euler/palindrome.h"

int
ull_is_pal(const ULL candidate, const int base)
{
	ULL num = candidate;
	ULL n = 0;

	while(num)
	{
		n = n * base + num % base;
		num /= base;
	}

	return candidate == n;
}

