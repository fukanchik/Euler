#include "euler/config.h"
#include "euler/reverse.h"

u8
ullreverse(u8 num)
{
	int ret = 0;

	while (num)
	{
		ret = ret * 10 + num % 10;
		num /= 10;
	}
	return ret;
}
