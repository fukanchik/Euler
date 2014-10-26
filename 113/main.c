#include <stdio.h>

#define UINT unsigned long long

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

int
main(int c, char *v[])
{
  UINT i;
  UINT nb;

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
  }
  printf("nb(10^6)=%llu\n", nb);
  nb=0;
  for(i=1;i<10000000000ull;++i) {
    int ii = isincr(i);
    int id = isdecr(i);
    if(ii || id) nb++;
    if(i%10000000==9999999)printf("%llu\n", i/10000000);
  }
  printf("nb=%llu\n", nb);
  return 0;
}
