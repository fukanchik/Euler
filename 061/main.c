#include <stdio.h>
#include <string.h>

int tri[10000];
int square[10000];
int penta[10000];
int hexa[10000];
int hepta[10000];
int octa[10000];

void filltri()
{
int i;
memset(tri, 0, sizeof(tri));
for(i=44;i<140;++i)
{
int p=i*(i+1)/2;
tri[p]=i;
}
}

void fillsquare()
{int i;
memset(square, 0, sizeof(square));
for(i=31;i<100;++i)
{
int p=i*i;
square[p]=i;
}
}

void fillpenta()
{
int i;
memset(penta, 0, sizeof(penta));
for(i=25;i<81;++i)
{
int p=i*(3*i-1)/2;
penta[p]=i;
}
}

void fillhexa()
{
    int i;
    memset(hexa,0, sizeof(hexa));
    for(i=22;i<70;++i)
    {
        int p=i*(2*i-1);
        hexa[p]=i;
    }
}

void fillhepta()
{
    int i;
    memset(hepta, 0, sizeof(hepta));
    for(i=20;i<64;++i)
    {
        int p=i*(5*i-3)/2;
        hepta[p]=i;
    }
}

void fillocta()
{
    int i;
    memset(octa, 0, sizeof(octa));
    for(i=18;i<59;++i)
    {
        int p=i*(3*i-2);
        octa[p]=i;
    }
}

#define TRI 1
#define SQ  2
#define PEN 4
#define HEX 8
#define HEPTA 16
#define OCTA 32

void foo(int n, int bits, int *l, int p);

int seqs[10];

void check(int k, int bits, int b, int *l, int p)
{
    int x=l[p];
    for(int i=0;i<100;++i)
    {
        int v=k*100+i;
        if(v<1000)continue;
        l[p]=v;
        seqs[p]=b;
        foo(v, bits|b, l, p+1);
    }
    l[p]=x;
}

void foo(int n, int bits, int *l, int p)
{
    if((bits&63)==63) {
        if((l[0]/100)==(n%100)) {
        int s=0;
        for(int i=0;i<p;++i)
        {
            printf("%d ", l[i]);
            s+=l[i];
        }
        printf("/");
        for(int i=0;i<p;++i) {
            int *a;
            switch(seqs[i]) {
            case TRI:
                a=tri;
                break;
            default:
                a=square;
                break;
            }
            printf("%d(%d) /%p/", seqs[i], tri[l[i]], (void*)a);
        }
        printf(" : %d\n",s);
        }
        return;
    }
    if((bits&TRI)==0 && tri[n]) {
        check(n%100, bits, TRI, l, p);
    }
    if((bits&SQ)==0 && square[n]) {
        check(n%100, bits, SQ, l, p);
    }
    if((bits&PEN)==0 && penta[n]) {
        check(n%100, bits, PEN, l, p);
    }
    if((bits&HEX)==0 && hexa[n]) {
        check(n%100, bits, HEX, l, p);
    }
    if((bits&HEPTA)==0 && hepta[n]) {
        check(n%100, bits, HEPTA, l, p);
    }
    if((bits&OCTA)==0 && octa[n]) {
        check(n%100, bits, OCTA, l, p);
    }
}

int
main(int argc, char* argv[])
{
    int i;
    int l[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

    filltri();
    fillsquare();
    fillpenta();
    fillhexa();
    fillhepta();
    fillocta();
    for(i=1000;i<10000;++i)
    {
        foo(i, 0, l, 0);
    }
	return 0;
}

