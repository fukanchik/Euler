#include <stdio.h>
#include <inttypes.h>

#define UINT unsigned long long

#define DIGIT 9
#define POWER 100

static UINT __nraise[POWER+1][11]={0};

static void
nraise_fill()
{
  UINT j, i;
  UINT sum;

  sum=9;
  for(i=1;i<=DIGIT;++i) {
    __nraise[1][i]=1;
  }
  for(j=2;j<=POWER;++j) {
    __nraise[j][1]=sum;
    for(i=2;i<=DIGIT;++i) {
      __nraise[j][i] = __nraise[j][i-1] - __nraise[j-1][i-1];
      sum += __nraise[j][i];
    }
  }
}

static UINT
nraiseN(UINT k)
{
  UINT sum = 0;
  UINT i;

  for(i=1;i<=DIGIT;++i) {
    sum += __nraise[k][i];
  }
  return sum;
}

static UINT __nfall[101][11]={0};

static void
nfall_fill()
{
  UINT j,i;

  for(i=0;i<=10;++i)
    __nfall[0][i]=1;

  __nfall[0][0]=1;
  for(j=1;j<=POWER;++j) {
    __nfall[j][0]=1;
    for(i=1;i<=10;++i) {
      __nfall[j][i]=__nfall[j-1][i]+__nfall[j][i-1];
    }
  }
}

static UINT
nfallN(UINT k)
{
  UINT i, sum;
  for(sum=0,i=1;i<=DIGIT;++i) {
    sum += __nfall[k-1][i];
  }
  return sum;
}

static UINT
calc(UINT n)
{
  return nraiseN(n) + nfallN(n) - 9;
}
int
main(int c, char *v[])
{
  UINT sum;
  UINT i;

  nraise_fill();
  nfall_fill();

  for(sum = 0, i = 1; i <= POWER; ++i) sum += calc(i);

  printf("%" PRIu64 "\n", sum);
  

  return 0;
}
