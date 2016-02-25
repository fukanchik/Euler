#include <stdio.h>
#include <malloc.h>

//E=2.71828182845904523536028747135266249775724709369995

#include <euler/config.h>
#include <euler/primes.h>
#include <euler/large.h>

#define COUNT 100

struct cf
{
  int number;
  struct large **recip;
};

static prime_list_t primes;

static void simplify(struct cf *cf);
static void fill_e_100(struct large **e);

static void
simplify(struct cf *cf)
{
  struct large * mnum = large_from_int(200, 1);
  struct large * fc = mnum;
  int i;

  for(i = cf->number - 1; i > 0; i--)
    {
      large_mul(cf->recip[i-1], cf->recip[i]);
      large_add(cf->recip[i-1], mnum);
      mnum = cf->recip[i];
    }
  cf->recip[1] = mnum;
  large_free(fc);
}

static void
fill_e_100(struct large **e)
{
  int i;
  int init = 2;

  e[0] = large_from_int(200, 2);

  for(i = 1; i < COUNT; ++i)
    {
      if((i-1) % 3 == 1)
	{
	  e[i] = large_from_int(200, init);
	  init += 2;
	}
      else
	{
	  e[i] = large_from_int(200, 1);
	}
    }
}

int
main(int argc, char* argv[])
{
  int i;

  primes_init_fill(&primes, 1000000);

  struct large ** e_100_r = malloc(sizeof(struct large *) * COUNT);
  struct cf e_100 = {.number=COUNT, .recip = e_100_r};

  fill_e_100(e_100_r);

  simplify(&e_100);

  printf("%d\n", large_sumdigits(e_100.recip[0]));

  primes_free(&primes);

  for(i = 0; i < COUNT; ++i)
    {
      large_free(e_100_r[i]);
    }
  free(e_100_r);

  return 0;
}
