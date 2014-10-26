#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

#include <euler/config.h>
#include <euler/assert.h>
#include <euler/large.h>

static char onebuf[]="\1";
static char tenbuf[]="\0\1\0";
static struct large onestruct = { onebuf, 1, 1};
static struct large tenstruct = { .buffer = tenbuf, .capacity = 3, .len = 2};
struct large* large_one = &onestruct;
struct large* large_ten = &tenstruct;

struct large*
large_new(int capacity)
{
	struct large* ret = malloc(sizeof(struct large));
	ret->buffer = malloc(capacity + 1);
	ret->capacity = capacity;
	ret->len = 1;

	memset(ret->buffer, 0, capacity + 1);

	return ret;
}

void
large_free(struct large* l)
{
  free(l->buffer);
  free(l);
}

struct large* large_from_int(int capacity, int val)
{
  struct large* ret = large_new(capacity);

  large_set(ret, val);

  return ret;
}

void
large_grow(struct large* l, int capacity)
{
  if(capacity < l->len) FAIL("Shrinking a number from %d to %d", l->len, capacity);

  char *b = malloc(capacity + 1);

  memset(b, 0, capacity + 1);
  memcpy(b, l->buffer, l->len);

  free(l->buffer);
  l->buffer = b;

  l->capacity = capacity;
}

void large_copy(struct large* dst, const struct large* src)
{
  if(dst->capacity < src->capacity) {
    free(dst->buffer);
    dst->buffer = malloc(src->capacity+1);
    dst->capacity = src->capacity;
  }

  memset(dst->buffer+src->len, 0, dst->capacity-src->len);
  memcpy(dst->buffer, src->buffer, src->len);

  dst->len = src->len;
}

int
large_iszero(struct large* num)
{
  return num->len==1 && num->buffer[0]==0;
}

int
large_len(struct large* l)
{
  return l->len;
}

struct large*
large_clone(struct large*l)
{
	struct large* ret = large_new(l->capacity);

	memcpy(ret->buffer, l->buffer, l->capacity);
	ret->len = l->len;

	return ret;
}

void
large_set(struct large* l, int num)
{
  int i;

  for(i=1;i<l->len;++i) {
    l->buffer[i]=0;
  }
  if(num == 0) {
    l->buffer[0] = 0;
    l->len = 1;
    return;
  }

  for(i=0; num > 0; ++i) {
    l->buffer[i] = num%10;
    num /= 10;
  }

  l->len = i;
}

int
large_coerce(struct large* num)
{
  int ret = 0;
  int i;

  for(i = num->len-1; i >= 0; --i) {
    ret = ret * 10 + num->buffer[i];
  }

  return ret;
}

int
large_is_palindrome(struct large* src)
{
  int pos = src->len - 1;
  int i;

  for(i=0; i < pos; i++, pos--) {
    if(src->buffer[i] != src->buffer[pos])
      return 0;
  }
  return 1;
}

struct large*
large_reverse(struct large *src)
{
  struct large* ret = large_new(src->capacity);
  int pos = src->len-1;
  int i;

  large_set(ret, 0);

  for(i = 0; pos >= 0; i++, pos--) {
    ret->buffer[i] = src->buffer[pos];
  }
  ret->len = src->len;

  return ret;
}

void
large_add(struct large* n1, struct large* n2)
{
  int minsz = MIN(n1->capacity, n2->len);
  int i;

  for(i = 0; i < minsz; ++i) {
    int num = n2->buffer[i];
    int start = i;
    int sum;

    do {
      sum = n1->buffer[start] + num;
      n1->buffer[start] = sum % 10;

      start = start + 1;
      num = sum / 10;
    } while(sum > 9 && start < n1->capacity);
    n1->len = MAX(start, n1->len);
  }
}

void
large_sub(struct large* top, struct large* bot)
{
  struct large* t = large_clone(bot);
  int i;

  for(i=t->capacity - 1;i>=0;--i) {
    t->buffer[i] = 9 - t->buffer[i];
  }
  t->len = t->capacity;

  large_add(t, large_one);
  large_add(top, t);
  /* Fix len. */
  for(i=top->capacity - 1; i >= 0;--i) {
    if(top->buffer[i])
      break;
  }

  top->len = i+1;
  if(top->len==0)top->len=1;

  large_free(t);
}

int
large_compare(struct large* n1, struct large* n2)
{
	int count;
	int i;

	if(n1==NULL||n2==NULL)return 0;

	count = MAX(n1->len, n2->len);

	for( i = count - 1; i >= 0; --i)
	{
		int v1 = n1->len > i ? n1->buffer[i] : 0;
		int v2 = n2->len > i ? n2->buffer[i] : 0;
		if(v1 != v2)
		{
			return v1 - v2;
		}
	}

	return 0;
}

static void
__sum0(char* n1, int start, int num)
{
	int sum = n1[start] + num;
	n1[start]=sum%10;
	if(sum>9) {
		__sum0(n1, start+1, sum/10);
	}
}

/*
    99
    82
   ---
   198
  792
  8118
*/
void
large_mul(struct large* n1, struct large* n2)
{
  int i, j, k;
  char *total = malloc(n1->capacity+1);
  memset(total, 0, n1->capacity+1);

  char *temp = malloc(n1->capacity+1);
  for(i = 0; i < n2->capacity-1; ++i) {
    memset(temp, 0, n1->capacity+1);

    for(j=0;j<n1->capacity-1;++j) {
      int digit = n2->buffer[i] * n1->buffer[j];
      temp[j] = temp[j] + digit % 10;
      if(digit > 9) {
	__sum0(temp, j+1, digit / 10);
      }
    }
    /*__dbg_print(temp, n1->size);*/
    for(k=0;k<n1->capacity-1-i;++k)
      {
	__sum0(total, k+i, temp[k]);
      }
    /*__dbg_print(total, n1->size);*/
  }
  free(temp);

  int last_zero = 0;
  free(n1->buffer);
  n1->buffer = total;
  for(k = 0; k < n1->capacity; ++k) {
    if(total[k] !=0)last_zero=k;
  }
  n1->len = last_zero + 1;
}

struct large*
large_div(struct large* top, struct large* bot)
{
  struct large* n, *nn;
  int len_top = top->len;
  int len_bot = bot->len;
  struct large* result = large_new(MAX(len_top, len_bot)*5);
  int cmp, plen;

  /* Divisor is zero. */
  if(large_iszero(bot))	{
    fprintf(stderr, "Division by zero\n");
    large_print(top);
    fprintf(stderr, "/0\n");
    abort();
  }

  /* Divident is zero. */
  if(large_iszero(top))	{
    large_set(result, 0);
    return result;
  }

  /* top shorter than bottom */
  if(len_top < len_bot)	{
    memset(top->buffer, 0, top->capacity);
    large_set(result, 0);
    return result;
  }

  cmp = large_compare(top, bot);
  if(cmp < 0) {
    /* Integer division. If divident is less than divisor we return 0. */
    memset(top->buffer, 0, top->capacity);
    large_set(result, 0);
    return result;
  }

  n = NULL;
  nn = NULL;
  plen = 0;

  while(1) {
    int count;

    n = large_new(top->capacity * 7);
    memcpy(n->buffer, bot->buffer, bot->capacity);
    n->len = bot->len;
    nn = large_clone(n);

    while(large_compare(top, n) >= 0) {
      if(nn) large_free(nn);
      nn = large_clone(n);
      large_mul(n, large_ten);
    }

    if(plen - 2 >= nn->len) {
      large_mul(result, large_ten);
      result->buffer[0]=0;
    }
    plen = nn->len;

    count=0;
    if(n)large_free(n);
    n = large_clone(nn);

    while(large_compare(top, nn) >= 0) {
      ++count;
      large_add(nn, n);
    }

    if(count)
      large_sub(nn, n);

    large_sub(top, nn);
    large_mul(result, large_ten);
    result->buffer[0] = count;

    if(large_iszero(top))
      break;
  }

  large_free(n);
  large_free(nn);

  return result;
}

struct large*
large_pow(int base, int expo)
{
	struct large* ret = large_new(base * expo + 1);
	struct large* lba = large_new(5);
	int i;
	large_set(lba, base);

	large_set(ret, base);
	for(i = 1; i < expo; ++i)
	{
		large_mul(ret, lba);
	}
	large_free(lba);
	return ret;
}

///Below junk
void
large_print(struct large* n1)
{
	int i;

	int s=0;
	for(i=n1->capacity-1;i>=0;--i)
	{
		if(!s&&n1->buffer[i]!=0) {
			s=1;
		}
		if(s)
			printf("%d", n1->buffer[i]);
	}
	if(!s) printf("0");
}

struct large*
large_factorial(int val)
{
	int i;
	struct large* ret = large_new(val*val+10);
	struct large* t = large_new(32);
	large_set(ret, 1);

	if(val==0||val==1) return ret;
	for(i=1;i <= val;++i)
	{
		large_set(t, i);
		large_mul(ret, t);
	}
	large_free(t);
	return ret;
}
