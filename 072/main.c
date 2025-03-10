#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <euler/number.h>
#include <euler/primes.h>

prime_list_t primes;

#define D 1000000

int pdenom[1000000];
int pnumer[1000000];

#define CACHESZ 500000
#define CACHEY 100
int cache[CACHESZ][CACHEY];

void
fillcache(void)
{
  if(primes.count>=CACHESZ) {
    abort();
  }
  for(int i=0;i<primes.count;++i) {
    int m=1;
    for(int j=0;m<5000000;j++) {
      if(j>=CACHEY) {
        abort();
      }
      cache[i][j]=m;
      m*=primes.primes[i];
    }
  }
}

int sumprimes(int *powers)
{
  int ret=1;

  for(int i=0;i<primes.count;++i)
    {
      int mul=cache[i][powers[i]];
      ret *= mul;
    }
  return ret;
}

int SUMDENOM=0;
int
generate(void)
{
  for(int i=0; i < primes.count; ++i) {
    pdenom[i]++;
    SUMDENOM = sumprimes(pdenom);
    if(SUMDENOM <= D) {
      return 1;
    }
    pdenom[i]=0;
  }
  return 0;
}

int SUMNUMER=1;

int gennumer(void)
{
  int flag=0;
  for(int i=0; i < primes.count; ++i) {
    if(pnumer[i]!=0) {
      flag=1;
      break;
    }
  }
  if(!flag) {
    pnumer[0]=-1;
    SUMNUMER=1;
    return 1;
  }
  if(pnumer[0]==-1) pnumer[0]=0;
  for(int i=0; i < primes.count; ++i) {
    if(pdenom[i]) continue;
    if(primes.primes[i] > SUMDENOM) continue;
    pnumer[i]++;
    //SUMNUMER = sumprimes(pnumer);
    int k=SUMNUMER*primes.primes[i];
    printf("%d %d %d\n", i, pnumer[i], k);
    if((SUMDENOM >= k) && (k <= D)) {
      SUMNUMER *= primes.primes[i];
      return 1;
    }
    int v=cache[i][pnumer[i]-1];
    if(v==0) {
      fprintf(stderr, "%d, %d, %d, %d\n", i, pnumer[i]-1, v, k);
      exit(0);
    }
    SUMNUMER /= v;
    pnumer[i]=0;
  }
  return 0;
}

int
main(int argc, char* argv[])
{
  unsigned long long count=0;

  primes_init_fill(&primes, D);
  fillcache();
  
  memset(pdenom, 0, sizeof(pdenom));
  while(1) {
    if(!generate()) break;
    printf("sum=%d %llu\n", SUMDENOM, count);
    memset(pnumer, 0, sizeof(pnumer));
    SUMNUMER=0;
    while(1) {
      if(!gennumer()) break;
      if(SUMDENOM < SUMNUMER) continue;
      //printf("...%d\n", SUMNUMER);
      count++;
    }
  }

  printf("%llu\n", count);
  return 0;
}
