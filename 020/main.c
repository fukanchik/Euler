#include <stdio.h>
#include <string.h>

#include <euler/large.h>

static struct large*
fact100()
{
  struct large* ret = large_new(600);
  struct large* m = large_new(10);
  int i;

  ret->buffer[0] = 1;
  for(i = 1; i <= 100; ++i)
    {
      large_set(m, i);
      large_mul(ret, m);
    }

  large_free(m);

  return ret;
}

int main(int argc, char* argv[])
{
  int sum2 = 0;
  int i;

  struct large* f100 = fact100();

  for(i = 0; i < f100->capacity; ++i)
    {
      sum2 += f100->buffer[i];
    }

  large_free(f100);

  printf("%d\n", sum2);

  return 0;
}
