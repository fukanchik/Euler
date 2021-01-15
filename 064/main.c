#include <stdio.h>
#include <math.h>

#define MAXN 1000

int M[MAXN];
int D[MAXN];
int A[MAXN];
int count = 0;

int
find(int m,int d, int a)
{
  int i;
  for(i=0;i<count;++i) {
    if(M[i]==m && D[i]==d && A[i]==a) {
      return i;
    }
  }
  return -1;
}

int c=0;
int
period(int s, int m, int d, int ap)
{
  if(c==MAXN)return -1;
  c++;

  int a0=sqrt(s);
  int m1=d*ap-m;
  int d1=(s-m1*m1)/d;
  int a1 = (a0 + m1)/d1;
  int cyc=find(m1,d1,a1);
  if(cyc!=-1) {
    int period = c-cyc;
    return period;
  }
  M[count] = m1;
  D[count] = d1;
  A[count] = a1;
  count++;
  return period(s, m1, d1, a1);
}

int
issquare(int n)
{
  int i;
  for(i = 2; i < 10000; ++i)
    {
      if((i*i) == n) return 1;
    }
  return 0;
}

int
main(int argc, char* argv[])
{
  int odds = 0;
  int N;

  for(N=2; N<=10000; ++N) {
    if(issquare(N)) continue;
    count=0;
    c=0;
    int a0=sqrt(N);
    M[count]=0;
    D[count]=1;
    A[count]=a0;
    count++;
  
    int per = period(N, 0, 1, a0);
    if(per==-1) {
      printf("ERROR\n");
      return 0;
    }
    if(per%2==1)odds++;
  }
  printf("%d\n", odds);
	return 0;
}
