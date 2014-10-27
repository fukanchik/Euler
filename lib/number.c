#include <euler/config.h>
#include <euler/assert.h>
#include <euler/number.h>

int num_len(int num)
{
  int len = 1;
  for(;num >= 10;len++) {
    num /= 10;
  }
  return len;
}

int num_upto(int num)
{
  int ret = 1;
  while(ret <= num) ret *= 10;
  return ret;
}

int num_concat(int n1, int n2)
{
  return n1 * num_upto(n2) + n2;
}

#if 0
  printf("%d,\t%d,\t%d,\t%d,\t%d,\t%d\n", 0, 2, 7, 10, 21, 133);
  printf("%d,\t%d,\t%d,\t%d,\t%d,\t%d\n", num_len(0), num_len(2), num_len(7), num_len(10), num_len(21), num_len(133));
  printf("%d,\t%d,\t%d,\t%d,\t%d,\t%d\n", num_upto(0), num_upto(2), num_upto(7), num_upto(10), num_upto(21), num_upto(133));

  printf("%d|%d=%d\n", 1,1, num_concat(1,1));
  printf("%d|%d=%d\n", 12,37, num_concat(12,37));
  printf("%d|%d=%d\n", 123,37, num_concat(123,37));
#endif
