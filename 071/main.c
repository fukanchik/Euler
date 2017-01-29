#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <euler/number.h>

#define NUM 3
#define DEN 7

/**
 * p/q < a/b
 * =>
 * p=(a*q-1)/b (-1 is necessary to exclude 3/7)
 */
int
main(int argc, char* argv[])
{
  long long lower_n = 0;
  long long lower_d = 1;
  long long d;

  for(d = 1000000; d > 1; --d)
    {
      long long n = (NUM * d - 1) / DEN;
      if(lower_n * d < n * lower_d)
        {
          lower_n = n;
          lower_d = d;
        }
    }
  printf("%lld %lld\n", lower_n, lower_d);
  return 0;
}
