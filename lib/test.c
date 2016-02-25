#include <stdio.h>

#include <euler/large.h>
#include <euler/assert.h>

static void
__assert(int x, char *ln, char *file, int line)
{
  if(!x) {
    FAIL("%s:%d %s", file, line, ln);
  }
}

#define ASSERT(x) __assert(x, #x, __FILE__, __LINE__);

static void allocated_ok(struct large *num, int cap, int len)
{
  ASSERT(num != NULL);
  ASSERT(num->capacity == cap);
  ASSERT(num->len == len);
  ASSERT(num->buffer != NULL);
}

static void
test_small()
{
  struct large *n;

  n=large_from_int(10, 1);
  if(large_len(n) != 1 )FAIL("1");
  large_free(n);
  n=large_from_int(10, 42);
  if(large_len(n) !=2 )FAIL("42");
  large_free(n);
  n=large_from_int(10, 221);
  if(large_len(n)!=3)FAIL("221");
  large_free(n);
  n = large_from_int(10, 7770);
  if(large_len(n)!=4)FAIL("7770");
  large_free(n);

  n=large_pow(2,3);
  if(large_coerce(n) != 8) FAIL("2^3");
  large_free(n);
  n=large_pow(1, 10);
  if(large_coerce(n) != 1) FAIL("1^10");
  large_free(n);
  n=large_pow(3, 3);
  if(large_coerce(n) != 27) FAIL("3^3");
  n=large_pow(12, 2);
  if(large_coerce(n) != 144) FAIL("12^2");
  large_free(n);

  n=large_pow(7,5);
  if(large_coerce(n) != 16807) FAIL("7^5");
  large_free(n);
}

int
main(int argc, char *argv[])
{
  struct large * lnum = large_new(10);
  struct large * l10 = large_from_int(100, 10);
  struct large * lclone = large_clone(l10);
  struct large * l10rev;

  ASSERT(1 == large_coerce(large_one));
  ASSERT(10 == large_coerce(large_ten));

  allocated_ok(lnum, 10, 1);

  allocated_ok(l10, 100, 2);
  ASSERT(10 == large_coerce(l10));

  ASSERT(large_iszero(lnum));
  ASSERT(!large_iszero(l10));

  ASSERT(lclone != NULL);
  ASSERT(lclone->capacity == 100);
  ASSERT(lclone->len == 2);
  ASSERT(lclone->buffer != NULL);
  ASSERT(10 == large_coerce(lclone));
  ASSERT(!large_iszero(lclone));

  ASSERT(large_len(lnum)==1);
  ASSERT(large_len(l10)==2);

  large_grow(l10, 200);
  allocated_ok(l10, 200, 2);
  ASSERT(l10->buffer[0] == 0);
  ASSERT(l10->buffer[1] == 1);

  large_grow(l10, 20);
  allocated_ok(l10, 20, 2);
  ASSERT(l10->buffer[0] == 0);
  ASSERT(l10->buffer[1] == 1);

  large_copy(lnum, l10);
  allocated_ok(lnum, 20, 2);
  ASSERT(lnum->buffer[0] == 0);
  ASSERT(lnum->buffer[1] == 1);

  large_set(l10, 0);
  ASSERT(l10->len == 1);
  large_set(l10, 391);
  ASSERT(l10->len == 3);
  ASSERT(l10->buffer[0]==1);
  ASSERT(l10->buffer[1]==9);
  ASSERT(l10->buffer[2]==3);
  ASSERT(!large_is_palindrome(l10));
  large_set(l10, 9);
  ASSERT(l10->len == 1);
  ASSERT(l10->buffer[0]==9);
  ASSERT(l10->buffer[1]==0);
  ASSERT(l10->buffer[2]==0);
  large_set(l10, 3113);
  ASSERT(large_is_palindrome(l10));
  large_set(l10, 393);
  ASSERT(large_is_palindrome(l10));
  large_set(l10, 3114);
  ASSERT(!large_is_palindrome(l10));

  large_set(l10, 42);
  l10rev = large_reverse(l10);
  ASSERT(l10rev != NULL);
  ASSERT(l10rev->capacity == 20);
  ASSERT(l10rev->len == 2);
  ASSERT(l10rev->buffer != NULL);
  ASSERT(l10rev->buffer[0] == 4);
  ASSERT(l10rev->buffer[1] == 2);
  large_free(l10rev);
  large_set(l10, 123);
  l10rev = large_reverse(l10);
  ASSERT(l10rev->len == 3);
  ASSERT(l10rev->buffer[0] == 1);
  ASSERT(l10rev->buffer[1] == 2);
  ASSERT(l10rev->buffer[2] == 3);
  large_free(l10rev);
  large_set(l10, 7);
  l10rev = large_reverse(l10);
  ASSERT(l10rev->len == 1);
  ASSERT(7 == large_coerce(l10rev));
  large_free(l10rev);

  large_set(lnum, 42);
  large_set(l10, 17);
  large_add(l10, lnum);
  ASSERT((17+42) == large_coerce(l10));
  ASSERT(42 == large_coerce(lnum));
  l10rev = large_new(10);
  large_set(l10rev, 995);
  ASSERT(l10rev->len==3);
  large_add(l10rev, lnum);
  ASSERT(l10rev->len==4);
  ASSERT((995+42) == large_coerce(l10rev));
  large_free(l10rev);

  large_set(l10, 100);
  large_set(lnum, 19);
  large_sub(l10, lnum);
  ASSERT((100-19) == large_coerce(l10));
  ASSERT(l10->len==2);

  large_set(l10, 17);
  large_set(lnum, 17);
  large_sub(l10, lnum);
  ASSERT(large_iszero(l10));

  large_set(l10, 100);
  large_set(lnum, 10);
  ASSERT(large_compare(l10, lnum) > 0);
  ASSERT(large_compare(lnum, l10) < 0);
  large_set(lnum, 100);
  ASSERT(large_compare(lnum, l10) == 0);
  large_set(l10, 111);
  large_set(lnum, 13);
  large_mul(l10, lnum);
  ASSERT((111 * 13) == large_coerce(l10));
  l10rev = large_div(l10, lnum);
  ASSERT(111 == large_coerce(l10rev));
  large_free(l10rev);
  l10rev = large_pow(2, 8);
  ASSERT(256 == large_coerce(l10rev));
  large_free(l10rev);
  l10rev = large_factorial(10);
  ASSERT(3628800 == large_coerce(l10rev));

  large_free(lnum);
  large_free(l10);

  printf("Ok\n");

  return 0;
}

void
test_large()
{
  struct large *n1 = large_new(10);
  struct large *n2 = large_new(10);

  n1->buffer[0]=0;
  n2->buffer[0]=3;

  large_free(n1);
  large_free(n2);
  n1 = large_new(1000);
  n2 = large_new(1000);
  n1->buffer[0]=1;
  n1->buffer[1]=0;
  n2->buffer[0]=2;
  n2->buffer[1]=0;
}
