#ifdef __PALINDROME_H__
#error "Double inclusion of palindrome.h"
#endif
#define __PALINDROME_H__

int is_palindrome(const int candidate, const int base);

#define ispal10(num) is_palindrome(num, 10)

#ifdef ULL_DEFINED
int ull_is_pal(const ULL candidate, const int base);
#endif

