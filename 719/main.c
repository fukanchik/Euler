#include <stdio.h>
#include <stdbool.h>
#include <euler/config.h>
#include <euler/number.h>

bool
is_s_num(u8 num)
{
	int digits[DIGITS_U8];
	int dlen = 0;

	if (!is_square(num))
		return false;

	num_to_digits(num, digits, &dlen);

	return false;
}

int
main(int argc, char* argv[])
{
	return 0;
}
