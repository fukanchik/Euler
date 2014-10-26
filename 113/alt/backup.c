#include <stdio.h>

#define UINT unsigned int

static int
isincr(UINT num)
{
  int prev = 10;
  while(num) {
    UINT digit = num % 10;
    num /= 10;
    if(digit > prev) return 0;
    prev = digit;
  }
  return 1;
}

static int
isdecr(UINT num)
{
  int prev=0;
  while(num) {
    UINT digit = num % 10;
    num /= 10;
    if(digit < prev) return 0;
    prev = digit;
  }
  return 1;
}

static int
calcnb(int from, int to)
{
  int nb = 0;
  int i;

  for(i=from;i<to;++i) {
    int ii = isincr(i);
    int id = isdecr(i);
    if(ii || id) nb++;
  }
  return nb;
}

static UINT
nraise0(UINT k, UINT n)
{
  UINT i;
  UINT sum;

  if(k==1)
    return 10-n;

  sum = 0;
  for(i=n;i<=9;++i) {
    sum += nraise0(k-1, i);
  }
  return sum;
}

static UINT
nraise(UINT k)
{
  return nraise0(k, 1);
}

static UINT
nfall0(UINT k, UINT n)
{
  if(n==1) return k;
  if(k==1) return 1;
  return nfall0(k-1, n)+nfall0(k, n - 1);
}

static UINT
nfall(UINT k)
{
  UINT i;
  UINT sum;

  sum = 0;
  for(i=1;i<=9;++i) {
    sum += nfall0(k, i);
  }
  return sum;
}

static UINT
calc(int n)
{
  return nraise(n)+nfall(n) - 9;
}
int
main(int c, char *v[])
{
  int i;
  int nb;
  UINT sum;

  printf("%d %d %d %d\n",
	 isincr(1234),
	 isincr(12334),
	 isincr(12343),
	 isincr(4321));
  printf("%d %d %d %d\n",
	 isdecr(43210),
	 isdecr(433210),
	 isdecr(433230),
	 isdecr(12340));

  nb=0;
  for(i=1;i<1000000;++i) {
    int ii = isincr(i);
    int id = isdecr(i);
    if(ii || id) nb++;
    //printf("%d %d %d\n", i, ii, id);
  }
  printf("nb=%d\n", nb);

  nb = calcnb(1, 10);
  printf("nb(1)=%d\n", nb);
  nb = calcnb(10, 100);
  printf("nb(2)=%d\n", nb);
  nb = calcnb(100, 1000);
  printf("nb(3)=%d\n", nb);
  nb = calcnb(1000, 10000);
  printf("nb(4)=%d\n", nb);
  nb = calcnb(10000, 100000);
  printf("nb(5)=%d\n", nb);
  nb = calcnb(100000, 1000000);
  printf("nb(6)=%d\n", nb);
  printf("calc(6)=%u\n", calc(6));

  printf("nr(1)=%u\n", nraise(1));
  printf("nr(2)=%u\n", nraise(2));
  printf("nr(3)=%u\n", nraise(3));
  printf("nr(4)=%u\n", nraise(4));
  printf("nr(5)=%u\n", nraise(5));
  printf("nr(6)=%u\n", nraise(6));

  printf("nf(1)=%u\n", nfall(1));
  printf("nf(2)=%u\n", nfall(2));
  printf("nf(3)=%u\n", nfall(3));
  printf("nf(4)=%u\n", nfall(4));
  printf("nf(5)=%u\n", nfall(5));
  printf("nf(6)=%u\n", nfall(6));

  sum = 0;
  for(i=1;i<=10;++i) {
    sum += calc(i);
  }
  printf("10^10=%u\n", sum);
  sum = 0;
  for(i=1;i<=100;++i) {
    time_t start = time(NULL);
    sum += calc(i);
    printf("i=%d - %u\n", i, time(NULL) - start);
  }
  printf("10^100=%u\n", sum);
  

  return 0;
}
