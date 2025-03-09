#include <euler/assert.h>
#include <euler/config.h>
#include <euler/number.h>

int gcd3(int n1, int n2);

int
num_len(int num)
{
	int len = 1;
	for (; num >= 10; len++)
	{
		num /= 10;
	}
	return len;
}

int
num_upto(int num)
{
	int ret = 1;
	while (ret <= num) ret *= 10;
	return ret;
}

int
num_concat(int n1, int n2)
{
	return n1 * num_upto(n2) + n2;
}

void
swap(int *i1, int *i2)
{
	int tmp = *i1;
	*i1     = *i2;
	*i2     = tmp;
}

int
gcd(int x, int y)
{
	while (y > 0)
	{
		int t = y;
		y     = x % y;
		x     = t;
	}
	return x;
}

int
gcd3(int n1, int n2)
{
	int prev = -1;

	while (n1 > 0)
	{
		prev = n1;
		while (n1 && n2 && n1 >= n2)
		{
			n1 = n1 - n2;
		}
		swap(&n1, &n2);
	}
	return prev;
}

int
ipow(int m, int n)
{
	int ret = 1; /* m^0 */

	for (int i = 0; i < n; ++i) ret *= m;

	return ret;
}

long
lpow(long m, long n)
{
	long ret = 1; /* m^0 */

	for (long i = 0; i < n; ++i) ret *= m;

	return ret;
}
