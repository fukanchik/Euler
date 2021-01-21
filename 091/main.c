#include <stdio.h>

#define N 50
#define MAXF 8192000

int FR0[MAXF];
int FC0[MAXF];
int FR1[MAXF];
int FC1[MAXF];
int FR2[MAXF];
int FC2[MAXF];
int FC=0;

int f0(int r0, int c0, int r1, int c1, int r2, int c2)
{
  for(int i=0;i<FC;++i) {
    if((FR0[i]==r0) && (FC0[i]==c0) && (FR1[i]==r1) && (FC1[i]==c1) && (FR2[i]==r2) && (FC2[i]==c2))
      return 1;
  }
  return 0;
}

int find(int r0, int c0, int r1, int c1, int r2, int c2)
{
  if(f0(r0,c0,r1,c1,r2,c2)) return 1;
  if(f0(r0,c0,r2,c2,r1,c1)) return 1;
  if(f0(r1,c1,r0,c0,r2,c2)) return 1;
  if(f0(r1,c1,r2,c2,r0,c0)) return 1;
  if(f0(r2,c2,r0,c0,r1,c1)) return 1;
  if(f0(r2,c2,c1,c1,r0,c0)) return 1;
  return 0;
}

void add(int r0, int c0, int r1, int c1, int r2, int c2)
{
  FR0[FC]=r0;
  FC0[FC]=c0;
  FR1[FC]=r1;
  FC1[FC]=c1;
  FR2[FC]=r2;
  FC2[FC]=c2;
  FC++;
}

void printt(int r0, int c0, int r1, int c1, int r2, int c2)
{
  if(find(r0,c0,r1,c1,r2,c2)) {
    return;
  }
  add(r0,c0,r1,c1,r2,c2);
  if(1)return;

  printf("%d: %d %d %d %d %d %d\n", FC, r0, c0, r1, c1, r2, c2);
  for(int r=0;r<=N;++r) {
    for(int c=0;c<=N;++c) {
      char ch='.';
      if( (r==r0&&c==c0)|| (r==r1&&c==c1) || (r==r2&&c==c2) ) {
        ch='*';
      }
      printf("%c", ch);
    }
    printf("\n");
  }
}

int numr(int n)
{
  int r0=0, c0=0;
  int r1,c1, r2,c2;
  for(r1 = 0; r1 <= n; ++r1) {
    for(c1 = 0; c1 <= n; ++c1) {
      for(r2 = 0; r2 <= n; ++r2) {
        for(c2 = 0; c2<= n; ++c2) {
          if(r1==r2 && c1==c2) continue;
          if(r1==r0 && c1==c0) continue;
          if(r0==r2 && c0==c2) continue;
          if(r0==r1 && r0==r2 && r1==r2) continue;
          if(c0==c1 && c0==c2 && c1==c2) continue;
          int ds10=(r1-r0)*(r1-r0) + (c1-c0)*(c1-c0);
          int ds12=(r1-r2)*(r1-r2) + (c1-c2)*(c1-c2);
          int ds20=(r2-r0)*(r2-r0) + (c2-c0)*(c2-c0);
          if((ds10+ds12)==ds20 || (ds10+ds20)==ds12 || (ds12+ds20)==ds10) {
            printt(r0,c0,r1,c1,r2,c2);
          }
        }
      }
    }
  }
  return FC;
}

int
main(int argc, char* argv[])
{
  printf("%d\n", numr(N));
	return 0;
}
