#include <stdio.h>
#include <euler/number.h>

#define NUMMAX 100

static int N[NUMMAX];
static int K[NUMMAX];
static int c;

static void
memoize(int n, int parts)
{
    N[c]=n;
    K[c]=parts;
    c++;
}

static int
findmem(int n)
{
    for(int i=0;i<c;++i)
    {
        if(N[i]==n)
            return K[i];
    }
    return -1;
}

/* Euler's Generator Function */
int P(int);
int
P(int n)
{
    int x;

    if((x=findmem(n)) != -1)
        return x;

    if(n<0)
        return 0;

    int sum=0;
    for(int k=1;k<=n;++k)
    {
        int p1 = n-k*(3*k-1)/2;
        int p2 = n-k*(3*k+1)/2;
        sum += ipow(-1, k+1)*(P(p1)+P(p2));
    }
    memoize(n, sum);
    return sum;
}

int main(int argc, char *argv[])
{
    N[0]=0;
    K[0]=1;
    c=1;
    printf("%d\n", P(NUMMAX) - 1 );
    return 0;
}

