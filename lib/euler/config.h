#ifdef __config_h__
#error "Double inclusion of config.h"
#endif

typedef unsigned char u1;
typedef unsigned long long u8;

#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
