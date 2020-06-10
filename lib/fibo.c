#include <euler/assert.h>
#include <euler/large.h>
#include <euler/fibo.h>

#define SIZE 100000

static struct large* ln1;
static struct large* ln2;
static int last=1;

void
large_fibo_init()
{
  last = 1;
  ln1 = large_from_int(SIZE, 1);
  large_set(ln1, 1);

  ln2 = large_from_int(SIZE, 1);
  large_set(ln2, 1);
}

void
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


