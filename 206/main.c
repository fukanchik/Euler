/* Backtracking solution. It extends the idea of rightmost two digits which produce 9_0 (30 and 70) to any length. */
#include <stdio.h>

#define TARGETLEN 19
#define TOOMUCH 19293949596979899ull

typedef unsigned long long ull;

//Count operations
static ull count=0;

#define N 20
ull P10[N];

static void initpowers()
{
   P10[0]=1;
   for(int i=1;i<N;++i) P10[i]=P10[i-1]*10;
}

static int check(ull num, int pos)
{
  int i;
  count++;
  for(i=0;i<=pos;i+=2)
  {
   int digit = (num / P10[i]) % 10;
   int expected = 9-i/2;
   if (digit != expected) {
     return 0;
   }
  }
  return 1;
}

static int backtrack(ull sofar, int len, int pos)
{
  if(sofar*sofar>TOOMUCH) return 0;
  if(pos==TARGETLEN) {
      printf("Found %llu which gives %llu\n", sofar*10, sofar*sofar*100);
      return 1;
  }
  int digit;
  for(digit=0; digit<10; ++digit)
  {
    ull num = digit*P10[len]+sofar;
    ull square=num*num;
    if(check(square, pos)) {
      if(backtrack(num, len+1, pos+1)) return 1;
    }
  }
  return 0;
}

int main(int argc, char *argv[])
{
  initpowers();
  backtrack(0,0,0);
  printf("Comparisons: %llu\n", count);
  return 0;
}

