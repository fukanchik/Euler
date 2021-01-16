#include <stdio.h>
#include <limits.h>

unsigned long long F[91];

static void
cache_fibo()
{
  F[0]=0;
  F[1]=1;
  for(int i=2;i<=90;++i) {
    F[i]=F[i-1]+F[i-2];
  }
}

unsigned long long int dsum(unsigned long long int n)
{
  unsigned long long int s = 0;
  while(n>0) {
    s+=n%10;
    n/=10;
  }
  return s;
}

unsigned long long int s(unsigned long long int n)
{
  for(unsigned long long int i = 0; i < ULLONG_MAX; ++i) {
    if(dsum(i)==n) return i;
  }
  return 0;
}

unsigned long long int S(unsigned long long int k)
{
  unsigned long long int n;
  unsigned long long int ret=0;
  for(n=1;n<=k;++n) {
    ret+=s(n);
  }
  return ret;
}

int
main(int argc, char *argv[])
{
  cache_fibo();
  for(int i=0;i<=90;++i) {
    printf("%d: %llu %llu\n", i, F[i], dsum(F[i]));
  }
  printf("%llu\n", s(89));
  return 0;
  printf("   %llu\n", ULLONG_MAX);
  printf("%llu\n", S(20));
  
  int i;
  for(i=2;i<=90;++i) {
    printf("%d: %llu %llu\n", i, F[i], S(F[i]));
  }
  return 0;
}
