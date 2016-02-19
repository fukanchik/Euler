#include <stdio.h>

#include <euler/config.h>
#include <euler/primes.h>

static prime_list_t primes;

/*
  Solved in MAXIMA first:

  lreduce(lambda([v1, v2], if second(v1) > second(v2) then v1 else v2),
  map(lambda([n], [n, n/block(
  [lst : ifactors(n),
  muls : map(lambda([x], (1-1/first(x))), ifactors(n))],
  n * product(muls[i], i, 1, length(lst))
  )]), makelist(i, i, 2, 1000000)) ) $
 
*/

int
main(int argc, char* argv[])
{
  primes_init_fill(&primes, 1000000);

  double maxratio = 0;
  int maxnum = 0;
  int num;

  for(num = 10; num <= 1000000; ++num)
    {
      int phi = totient(&primes, num);

      double ratio = (double)num/(double)phi;

      if(unlikely(ratio > maxratio))
	{
	  maxratio = ratio;
	  maxnum = num;
	}
    }

  printf("%d\n", maxnum);

  return 0;
}
