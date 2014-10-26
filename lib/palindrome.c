#include "euler/palindrome.h"

int
is_palindrome(const int candidate, const int base)
{
	int num = candidate;
	int n = 0;

	while(num)
	{
		n = n * base + num % base;
		num /= base;
	}

	return candidate == n;
}

