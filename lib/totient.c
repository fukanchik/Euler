#include <euler/primes.h>

/*
  May be also speedup:
  * if prime(a) then totient(a) = a - 1;
  * if a=prime(p)^n, then totient(a) = p^n-p^{n-1}
  * if GCD(a,b) = 1, then totient(a*b) = totient(a)*totient(b)
  * totient(n) = n(1-1/p1)*(1-1/p2)*...*(1-1/pk).
*/

struct _t2
{
  int num;

  int numerator;
  int denominator;
};

static bool collect(const prime_list_t * const primes, u8 prime, void *arg);

static inline bool
collect(const prime_list_t * const primes, u8 prime, void *arg)
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
