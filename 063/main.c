#include <stdio.h>

#include <euler/config.h>
#include <euler/assert.h>

#include <euler/large.h>

int main(int argc, char *argv[])
{
  struct large *n;
  ULL i, j;

  for(i=1;i<100;++i) {
    for(j=0;;++j) {
      ULL nlen;
      n = large_pow(j, i);
      nlen=large_len(n);
      if(nlen > i) break;

      if(nlen == i) {
	printf(ULLFMT "^" ULLFMT "=" , j, i);
	large_print(n);
	printf("\n");
      }
      large_free(n);
    }
  }
  return 0;
}

