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

struct _t2
{
  int num;

  int numerator;
  int denominator;
};

static int collect(const prime_list_t * const primes, int prime, void *arg);

static inline int
collect(const prime_list_t * const primes, int prime, void *arg)
{
  struct _t2 *t = arg;
  int exp = 0;

  if(unlikely(prime > t->num))
    return 1;

  while(t->num % prime == 0)
    {
      t->num /= prime;
      exp++;
    }
  if(unlikely(exp != 0))
    {
      t->numerator *= prime;
      t->denominator *= (prime - 1);
    }

  return 0;
}

int
main(int argc, char* argv[])
{
  primes_init_fill(&primes, 1000000);

  double maxratio = 0;
  int maxnum = 0;
  int num;

  for(num = 10; num <= 1000000; ++num)
    {
      struct _t2 t2 = {.num=num,
		       .numerator=1,
		       .denominator=1};

      primes_for_each(&primes, collect, &t2);

      int phi = t2.denominator * (num / t2.numerator);

      double ratio = (double)num/(double)phi;

      if(unlikely(ratio > maxratio))
	{
	  maxratio=ratio;
	  maxnum=num;
	}
    }

  printf("%d\n", maxnum);

  return 0;
}
