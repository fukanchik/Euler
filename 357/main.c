#include <stdio.h>
#include <euler/primes.h>

int divisors(int n);

prime_list_t primes;

int divisors(int n)
{
  int d;
  for(d=1;d<=n;d++) {
    if(n%d!=0) continue;
    if(!primes_is_prime(&primes, d + n / d)) return 0;
  }
  return 1;
}

int
main(int argc, char* argv[])
{
  unsigned long long int sum=0;
  primes_init_fill(&primes, 1000000);
  int i;
  for(i=1;i<=100000000;++i) {
    if(i%1000000==0) printf("%d\n", i);
    int r30=divisors(i);
    if(!r30) continue;
    sum+=i;
    //printf("n=%d\n", i);
  }
  printf("%lld\n", sum);
	return 0;
}
