#ifdef _WIN32
typedef __int64 ULL;
#define ULLFMT "%I64u"
#else
typedef unsigned long long ULL;
#define ULLFMT "%llu"
#endif
#define ULL_DEFINED

typedef unsigned char u1;

#ifndef _WIN32
#define O_BINARY 0
#endif

#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
