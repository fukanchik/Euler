#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ull;
static int check(ull n);

//Count operations
static ull count=0;

static int check(ull n)
{
  count++;

  int d0=n%10;
  n/=100;
  int d2=n%10;
  n/=100;
  int d4=n%10;
  n/=100;
  int d6=n%10;
  n/=100;
  int d8=n%10;
  n/=100;
  int d10=n%10;
  n/=100;
  int d12=n%10;
  n/=100;
  int d14=n%10;
  n/=100;
  int d16=n%10;
  n/=100;
  int d18=n%10;
  n/=10;

  if(d0!= 0) return 0;
  if(d2!= 9) return 0;
  if(d4!= 8) return 0;
  if(d6!= 7) return 0;
  if(d8!= 6) return 0;
  if(d10!=5) return 0;
  if(d12!=4) return 0;
  if(d14!=3) return 0;
  if(d16!=2) return 0;
  if(d18!=1) return 0;
  if(n!=0) return 0;
  return 1;
}

int main(int argc, char *argv[])
{
  ull low=10101010ull;//[sqrt(102030405060708090)]/100
  ull up=1389026623ull;//[sqrt(102030405060708090)]/100
  ull i;

  for(i=low;i<up;i+=1)
  {
    ull p = i*100+30;
    if (check(p*p)) {
      printf("Found: %llu: %llu\n", p,p*p);
      printf("Count: %llu\n", count);
      return 0;
    }
  }
   for(i=low;i<up;i+=1)
  {
    ull p = i*100+70;
    if (check(p*p)) {
      printf("Found: %lld: %lld\n", p,p*p);
      printf("Count: %llu\n", count);
      return 0;
    }
  }
 
 return 0;
}

