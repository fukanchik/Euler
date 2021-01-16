#include <stdio.h>
#include <stdlib.h>
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

static struct large *
s(struct large *n)
{
    struct large *one = large_new(SIZE);
    large_set(one, 1);
    struct large * nine = large_new(SIZE);
    large_set(nine, 9);
    struct large * ten = large_new(SIZE);
    large_set(ten, 10);

    struct large *n0 = large_clone(n);
    struct large * x = large_div(n0, nine);
    struct large *tmp =large_clone(x);
    large_mul(tmp, nine);
    struct large * r = large_clone(n);
    large_mul(r, tmp);
    large_free(tmp);
    struct large * ret = large_new(SIZE);

    large_copy(ret, r);

    printf(" n=");
    large_print(n);
    printf(" x=");
    large_print(x);
    printf(" r=");
    large_print(r);
    printf("\n");
    exit(0);

    struct large *i = large_new(SIZE);
    large_set(i, 0);
    for( ; large_compare(i, x) < 0 ; )
    {
        large_mul(ret, ten);
        large_add(ret, nine);

        large_add(i, one);

        large_print(i);
        printf(",");
        large_print(x);
        printf(" ");
        large_print(ret);
        printf("\n");
    }

    return ret;
}

static struct large *
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
        fflush(stdout);
        struct large *f = fibo_cache[i];
        large_add(ret, S(f));
    }
}

int
main(int argc, char* argv[])
{
    struct large *ten = large_new(2);
    struct large *twenty= large_new(2);
    large_fibo_init();
    cache_fibo(90);
    large_set(ten, 10);
    large_set(twenty, 20);

    struct large * t = s(ten);
    large_print(t);
    printf("\n");
    t = s(twenty);
    large_print(t);
    printf("\n");

    F();

	return 0;
}
