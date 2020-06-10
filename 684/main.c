#include <stdio.h>
#include <malloc.h>
#include <euler/assert.h>
#include <euler/large.h>
#include <euler/fibo.h>

#define SIZE 1000

static struct large **fibo_cache;

static void
cache_fibo(int nmax)
{
    int i;

    fibo_cache = malloc(sizeof(struct large*) * (nmax+1) );
    if(!fibo_cache) {
        FAIL("NO MEM");
    }

    for(i = 0; i <= nmax; ++i)
    {
        fibo_cache[i] = large_new(SIZE);
        if(!fibo_cache[i]) {
            FAIL("NO MEM2");
        }
        large_fibo(fibo_cache[i], i);
    }
}

struct large *
s(int n)
{
    int i;
    int x = n / 9;
    int r = n % 9;

    struct large * ret = large_new(SIZE);
    struct large * ten = large_new(SIZE);
    struct large * nine = large_new(SIZE);

    large_set(ret, r);
    large_set(ten, 10);
    large_set(nine, 9);

    for(i=0; i < x; ++i)
    {
        large_mul(ret, ten);
        large_add(ret, nine);
    }

    return ret;
}

struct large *
S(struct large *k)
{
    struct large *i = large_new(SIZE);
    struct large *res = large_new(SIZE);
    struct large *one = large_new(SIZE);
    large_set(res, 0);
    large_set(one, 1);

    large_set(i, 1);
    for(; large_compare(i, k);)
    {
       struct large *p = s(i);
        large_add(res, p);
        large_add(i, one);
    }
    return res;
}

static void
F()
{
    int i;

    struct large* ret = large_new(SIZE);
    large_set(ret, 0);
    for(i=2;i<=90;++i)
    {
        printf("%d\n", i);
        struct large *f = fibo_cache[i];
        large_add(ret, S(f));
    }
}

int
main(int argc, char* argv[])
{   
    large_fibo_init();
    cache_fibo(90);

    struct large * t = s(10);
    large_print(t);
    printf("\n");
    t = s(20);
    large_print(t);
    printf("\n");

    F();

	return 0;
}
