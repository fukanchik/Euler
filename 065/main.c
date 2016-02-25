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
static void divisors(struct large *v1, struct large *v2);

static void
divisors(struct large *v1, struct large *v2)
{
  int i;

  for(i = 0; i < primes.count; ++i)
    {
      struct large *prime = large_from_int(200, primes.primes[i] );
      struct large *d1 = large_div(v1, prime);
      large_mul(d1, prime);
      struct large *d2 = large_div(v2, prime);
      large_mul(d2, prime);
      
      while(large_compare(v1, d1) == 0 && large_compare(v2, d2) == 0)
	{
	  v1 = large_div(v1, prime);
	  v2 = large_div(v2, prime);
	}
    }
}

static void
simplify(struct cf *cf)
{
  int i;
  struct large * mnum = large_from_int(200, 1);

  for(i = cf->number - 1; i > 0; i--)
    {
      large_mul(cf->recip[i - 1], cf->recip[i]);
      large_add(cf->recip[i - 1], mnum);
      mnum = cf->recip[i];

      //divisors(cf->recip[i - 1], mnum);
    }
  cf->recip[1] = mnum;
}

static void
fill_e_100(struct large **e)
{
  int i;
  int init = 2;
  e[0] = large_from_int(200, 2);

  for(i=1;i<COUNT;++i)
    {
      if((i-1)%3==1)
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
  struct large* sqrt_2_r[10];
  int sqrt_2_r_i[] = {1,2,2,2,2,2,2,2,2,2};
  for(i=0;i<10;++i)
    {
      sqrt_2_r[i] = large_from_int(200, sqrt_2_r_i[i]);
    }
  struct cf sqrt_2 = {.number=10, .recip=sqrt_2_r};
  struct large * e_r[10];
  int e_r_i[] = {2,1,2,1,1,4,1,1,6,1};
  for(i=0;i<10;++i)
    {
      e_r[i] = large_from_int(200, e_r_i[i]);
    }
  struct cf e = {.number=10, .recip = e_r};
  struct large ** e_100_r = malloc(sizeof(struct large *) * COUNT);
  fill_e_100(e_100_r);
  struct cf e_100 = {.number=COUNT, .recip = e_100_r};


  simplify(&sqrt_2);
  simplify(&e);
  simplify(&e_100);

  printf("sqrt(2) = ");
  large_print(sqrt_2.recip[0]);
  printf("/");
  large_print(sqrt_2.recip[1]);
  printf("\n");
  printf("e = ");
  large_print(e.recip[0]);
  printf("/");
  large_print(e.recip[1]);
  printf("\n");
  printf("e_100 = ");
  large_print(e_100.recip[0]);
  printf("/");
  large_print(e_100.recip[1]);
  printf("\n");

  return 0;
}
