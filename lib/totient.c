#include <euler/config.h>
#include <euler/primes.h>

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
totient(prime_list_t * primes, int num)
{
  struct _t2 t2 = {.num=num,
		   .numerator=1,
		   .denominator=1};

  primes_for_each(primes, collect, &t2);

  return t2.denominator * (num / t2.numerator);
}
