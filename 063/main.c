#include <stdio.h>

#include <euler/config.h>
#include <euler/assert.h>

#include <euler/large.h>

int main(int argc, char *argv[])
{
  struct large *n;
  u8 i, j;

  for(i=1;i<100;++i) {
    for(j=0;;++j) {
      u8 nlen;
      n = large_pow(j, i);
      nlen=large_len(n);
      if(nlen > i) break;

      if(nlen == i) {
	printf("%llu^%llu=" , j, i);
	large_print(n);
	printf("\n");
      }
      large_free(n);
    }
  }
  return 0;
}
