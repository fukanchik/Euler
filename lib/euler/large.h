#ifdef __cplusplus
extern "C" {
#endif

struct large
{
  char *buffer;
  int capacity;
  int len;
};

extern struct large *large_one, *large_ten;

/* Allocate a large number and initialize it to 0. */
struct large* large_new(int capacity);
/* Allocate a large number and initialize it to val. */
struct large* large_from_int(int capacity, int val);
/* Free large number. */
void large_free(struct large*);

void large_grow(struct large* l, int capacity);
struct large* large_clone(struct large* l);
void large_copy(struct large* dst, const struct large* src);

int large_len(struct large* l);
int large_iszero(struct large* num);
int large_compare(struct large* n1, struct large* n2);
int large_is_palindrome(struct large* src);
int large_sumdigits(struct large* src);

void large_set(struct large*, int num);
int large_coerce(struct large*);

  /* top = top  - bot */
void large_sub(struct large* top, struct large* bot);
  /* n1 = n1 + n2 */
void large_add(struct large* n1, struct large* n2);
  /* n1 = n1 * n2 */
void large_mul(struct large* n1, struct large* n2);
struct large* large_div(struct large* top, struct large* bot);
struct large* large_pow(int base, int expo);
struct large* large_factorial(int val);
struct large* large_reverse(struct large *src);

void large_print(struct large* n1);

#ifdef __cplusplus
}
#endif
