#include <stdio.h>

#include <euler/number.h>
#include <euler/reverse.h>

static int
is_reversible(int num)
{
  int rev = reverse(num);
  int sum = num + rev;
  if(num_len(num)!=num_len(rev)) return 0;

  while(sum > 0) {
    int digit = sum % 10;
    sum /= 10;
    if(digit % 2 ==0) return 0;
  }
  return 1;
}

int
main(int argc, char *argv[])
{
  int i;
  int count;

  for(i = 1, count=0;i<1000000000;++i) {
    int is = is_reversible(i);
    count += is;
  }

  printf("%d\n", count);

  return 0;
}
