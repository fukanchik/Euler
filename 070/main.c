#include <stdio.h>

#include <euler/number.h>
#include <euler/primes.h>

/* This is quite stupid brute force implementation.
 */

#define TOP_LIMIT 10000000

static prime_list_t primes;

int
main(int argc, char* argv[])
{
  primes_init_fill(&primes, TOP_LIMIT);

  double minratio = TOP_LIMIT;
  int minnum = 0;
  int num;

  for(num = TOP_LIMIT - 1; num >= 2; --num)
    {
      int phi = totient(&primes, num);
      if(!is_permutation(num, phi))
	continue;

      double ratio = (double)num/(double)phi;

      if(unlikely(ratio < minratio))
	{
	  minratio=ratio;
	  minnum=num;
	}
    }

  printf("%d\n", minnum);

  return 0;
}
