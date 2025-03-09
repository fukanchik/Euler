#include <stdio.h>

#include <euler/config.h>

#define MAX2 100000000ull
#define NPRIMES nprimes

static u8 primes[MAX2];
static u8 nprimes;

static void prime_add(u8 i)
{
  primes[nprimes++]=i;
}

static int
isprime(u8 num)
{
	u8 i;

  for(i=0;i<nprimes;++i) {
    if(num <= primes[i]) break;
    if((num%primes[i]) == 0) return 0;
  }
  return 1;
}

static void
fill_primes(void)
{
	u8 i;

  primes[0]=2;
  nprimes=1;
  for(i = 3; i < MAX2; i+=2) {
    if(isprime(i)) prime_add(i);
    if((i%100000)==1) printf("nprimes=%llu %llu\n", nprimes, i);
  }
}

static void print_primes(void)
{
  int i;
  for(i=0;i<100;++i) {
    printf("%d ", (int)primes[i]);
  }
}

static int
count_below(u8 n)
{
  unsigned j, i;
  int ret=0;

  for(j = 0; j < NPRIMES; j++) {
    for(i = j; j < NPRIMES; ++i) {
		u8 num = primes[j] * primes[i];
      if(num > n) {
        break;
      }
      ret++;
    }
  }
  return ret;
}

int
main(int argc, char *argv[])
{
  fill_primes();
  print_primes();
  printf("nprimes=%llu\n", nprimes);
  printf("f(30)=%d\n", count_below(30));
  printf("f(10^8)=%d\n", count_below(100000000ull));

  return 0;
}
