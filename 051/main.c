#include <stdio.h>
#include <string.h>

#include <euler/primes.h>
#include <stdlib.h>
#include <euler/number.h>

#define MAXPRIME 1000000

prime_list_t primes;

void explode(int num, int *buf, int len);
int implode(int *buf, int len);
int allbits(int len);
bool find_groups(const prime_list_t * const pl, u8 prime);
static void __set(int *buf, int len, int digit, int mask);
int set(int prime, int len, int digit, int mask);


void
explode(int num, int *buf, int len)
{
  int i;

  for(i = 0; i < len; ++i)
    {
      buf[i] = num % 10;
      num /= 10;
    }
}

int
implode(int *buf, int len)
{
  int i;
  int ret = 0;

  for(i = len - 1; i >= 0; --i)
    {
      ret *= 10;
      ret += buf[i];
    }
  return ret;
}

int
allbits(int len)
{
  int mask = 1;
  int ret = 0;
  int i;

  for(i = 0; i < len; ++i)
    {
      ret |= mask;
      mask = mask << 1;
    }
  return ret;
}

static void
__set(int *buf, int len, int digit, int mask)
{
  int pos;
  int v = 1;

  for(pos = 0; pos < len; ++pos)
    {
      if(mask & v)
	{
	  buf[pos] = digit;
	}
      v = v<<1;
    }
}

int
set(int prime, int len, int digit, int mask)
{
  int buf[100];
  memset(buf, 0, sizeof(int) * 100);

  explode(prime, buf, len);
  __set(buf, len, digit, mask);
  return implode(buf, len);
}

bool
find_groups(const prime_list_t * const pl, u8 prime)
{
  int len = num_len(prime);
  int mask_max = allbits(len - 1);

  int i;
  for(i = 1;i <= mask_max; ++i)
    {
      int mask = i << 1;// We need /2 times. leftmost gives only 1,3,7,9
      int count = 0;
      int hits[10];
      int digit;

      memset(hits, 0, sizeof(int) * 10);
      for(digit = 0;digit <= 9; ++digit)
	{
	  int num = set(prime, len, digit, mask);
	  if(num_len(num) != len)
	    {
	      continue;
	    }
	  if(primes_is_prime(pl, num))
	    {
	      count++;
	      hits[digit]++;
	    }
	}
      if(count == 8)
	{
	  int m;
	  for(m = 0; m < 10; ++m)
	    {
	      if(hits[m] != 0)
		{
		  int num = set(prime, len, m, mask);
		  printf("%d\n", num);
		  return 1;
		}
	    }
	}
    }

  return 0;
}

int
main(int argc, char *argv[])
{
  primes_init_fill(&primes, MAXPRIME);

  primes_for_each_simple(&primes, find_groups);

  return 0;
}
