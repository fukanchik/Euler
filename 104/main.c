#include <stdio.h>

#include <euler/large.h>
#include <euler/assert.h>

#define SIZE 100000

struct large* ln1;
struct large* ln2;
int last=1;

static void
large_fibo(struct large* out, int num)
{
  int i;

  if(num==0||num==1||num==2) {
    large_set(out, 1);
    return;
  }

  if(num - last < 1) {
    FAIL("%d - %d", num, last);
  }
  for(i = last+1;i <= num;i++) {
    struct large* lnt;

    large_add(ln1, ln2);

    lnt = ln1;
    ln1 = ln2;
    ln2 = lnt;
  }
  large_copy(out, ln1);
  last = num;
}

static int
large_is_pandigital1_9(struct large* num, int dir)
{
  int val[10]={0};
  int i;

  if(dir==0) {
    for(i=0;i<9;++i) {
      int digit = num->buffer[i];
      //if(digit>9) FAIL("Corrupt large num(1).");
      //if(digit<0) FAIL("Corrupt large num(2).");
      val[digit]++;
    }
  } else {
    int len = large_len(num);
    for(i=len-1;i>=len-9;--i) {
      int digit = num->buffer[i];
      //if(digit>9) FAIL("Corrupt large num(1).");
      //if(digit<0) FAIL("Corrupt large num(2).");
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

  ln1 = large_from_int(SIZE, 1);
  ln2 = large_from_int(SIZE, 1);
  large_set(ln1, 1);
  large_set(ln2, 1);

  int i;
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
