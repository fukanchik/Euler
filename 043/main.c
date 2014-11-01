#include <stdio.h>

static int nums[]={
  2,3,5,7,11,13,17
};

static int
pan(long long val)
{
  int d[10];
  int i;
  int sum;

  for(i=0;i<10;++i)d[i]=0;

  while(val !=0) {
    int n = val % 10;
    d[n]=1;
    val /= 10;
  }

  sum = 0;

  for(i=0;i<10;++i)sum+=d[i];

  return sum==10;
}

static int
three(long long v, int n)
{
  long v0;
  int i;
  for(v0=1, i=0;i<8-n;++i)v0*=10;
  return (v / v0) % 1000;
}

static int
sum(int v, int t)
{
  return v%nums[t]==0;
}

static int prop(long long n)
{
  if(!pan(n)) return 0;

  int p2 = three(n, 2);
  int t2 = sum(p2, 0);
  int t3 = sum(three(n, 3), 1);
  int t4 = sum(three(n, 4), 2);
  int t5 = sum(three(n, 5), 3);
  int t6 = sum(three(n, 6), 4);
  int t7 = sum(three(n, 7), 5);
  int t8 = sum(three(n, 8), 6);

  printf("%d:%d %d %d %d %d %d %d\n", p2, t2, t3, t4, t5, t6, t7, t8);
  return t2 && t3 && t4 && t5 && t6 && t7 && t8;
}

int main(int argc, char *argv[])
{
  long long n;
  long long k = 1406357289;

  printf("%d\n", three(k, 8));
  printf("%d\n", prop(k));
  for(n = 0; n < 9999999999ll; n++) {
    if(prop(n)) {
      printf("%lld\n", n);
    }
  }
  return 0;
}
