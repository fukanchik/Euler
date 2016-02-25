#include <stdio.h>
#include <math.h>

#include <euler/primes.h>

#define MAXNUM 1000000

static prime_list_t primes;

static int
numdivs3(int num)
{
  int i;
  int numdivs = 1;

  for(i = 0;  i < primes.count; ++i)
    {
      int count = 0;

      while(num % primes.primes[i]==0)
	{
	  count++;
	  num /= primes.primes[i];
	}
      if(count != 0)
	{
	  numdivs *= count + 1;
	}
    }
  return numdivs;
}

int
main(int argc, char* argv[])
{
  int i;
  int triangle_number;

  primes_init_fill(&primes, sqrt(MAXNUM) + 1);

  for(triangle_number = 0, i = 1; i < MAXNUM; ++i)
    {
      triangle_number += i;
      if(numdivs3(triangle_number) > 500) {
	printf("%d\n", triangle_number);
	break;
      }
    }

  primes_free(&primes);

  return 0;
}
