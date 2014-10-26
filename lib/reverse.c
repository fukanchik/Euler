#include "euler/reverse.h"

int
reverse(int num)
{
	int ret = 0;

	while(num)
	{
		ret = ret * 10 + num % 10;
		num /= 10;
	}
	return ret;
}
