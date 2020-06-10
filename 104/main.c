#include <stdio.h>

#include <euler/large.h>
#include <euler/assert.h>
#include <euler/fibo.h>

#define SIZE 100000
static int
large_is_pandigital1_9(struct large* num, int dir)
{
  int val[10]={0};
  int i;

  if(dir==0) {
    for(i=0;i<9;++i) {
      int digit = num->buffer[i];
      val[digit]++;
    }
  } else {
    int len = large_len(num);
    for(i=len-1;i>=len-9;--i) {
      int digit = num->buffer[i];
      val[digit]++;
    }
  }
  for(i=1;i<10;++i) {
    if(val[i] != 1)
      return 0;
  }
  return 1;
}

int main(int argc, char *argv[])
{
  struct large* ln = large_new(SIZE);

  int i;

  large_fibo_init();
#define TOP 1000000000
  for(i=1;i <= TOP;++i) {
    large_fibo(ln, i);
    
    if((i%10000)==9999) {
      printf("%d %d\n", i, ln->len);
      if(ln->len+1000>SIZE) FAIL("MOAR!");
    }
    //large_print(ln);
    //printf("\n");
    if(large_is_pandigital1_9(ln, 0) && large_is_pandigital1_9(ln, 1)) {
      large_print(ln);
      printf("\n%d Is Pan FIRST\n", i);
      break;
    }
  }
  //large_print(ln);
  printf("\n");

  return 0;
}
