#include "euler/config.h"
#include "euler/reverse.h"

ULL
ullreverse(ULL num)
{
	int ret = 0;

	while(num)
	{
		ret = ret * 10 + num % 10;
		num /= 10;
	}
	return ret;
}
