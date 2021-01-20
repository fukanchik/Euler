#include <stdio.h>
#include <euler/large.h>

/*
 * Use algorithm from http://www.afjarvis.staff.shef.ac.uk/maths/jarvisspec02.pdf
 * to calculate digits array.
 */
//allow extra space b/c lowest few digits are not always accurate
#define MAXLEN 110

struct large *TEN;
struct large *FIVE;

struct large *sqrt_digits(int n)
{
  struct large *a = large_from_int(MAXLEN, n * 5);
  struct large *b = large_from_int(MAXLEN, 5);

  while(b->len < MAXLEN) {
    if(large_compare(a, b) >= 0) {
      large_sub(a, b);
      large_add(b, TEN);
    } else {
      large_shift_left(a, 2);
      large_shift_right(b, 1);
      large_shift_left(b, 2);
      large_add(b, FIVE);
    }
  }
  
  large_free(a);
  large_shift_right(b, b->len-100);

  return b;
}

int
main(int argc, char* argv[])
{
  FIVE = large_from_int(MAXLEN, 5);
  TEN = large_from_int(MAXLEN, 10);

  int sum=0;

  int n=1;
  for(int i=1;i<=100;i++) {
    if(n*n==i) {
      n++;
      continue;
    }

    struct large *x = sqrt_digits(i);
    sum += large_sumdigits(x);
    large_free(x);
  }

  large_free(FIVE);
  large_free(TEN);

  printf("%d\n", sum);

	return 0;
}
