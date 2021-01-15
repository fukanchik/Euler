#include <stdio.h>
#include <string.h>

#define MAXN 6

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

  for(i = 44; i < 142; ++i)
    {
      int p=i*(i+1)/2;
      tri[p]=i;
    }
  int c=0;
  for(i=0;i<10000;++i) {
    if(tri[i]!=0) c++;
  }
}

void fillsquare()
{
  int i;
  memset(square, 0, sizeof(square));
  for(i=31;i<100;++i)
    {
      int p=i*i;
      square[p]=i;
    }
  int c=0;
  for(i=0;i<10000;++i) {
    if(square[i]!=0) c++;
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
  int c=0;
  for(i=0;i<10000;++i) {
    if(penta[i]!=0) c++;
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


int bar3(int *nums, int pos);
int bar4(int *nums, int pos, int *busy, int bp);

int *ARRS[MAXN]={tri, square, penta, hexa, hepta, octa};
int BPS[MAXN];

void dump(int *num)
{
  int i;
  int sum=0;

  for(i=0;i<MAXN;++i) {
    sum+=num[i];
  }
  printf("%d\n", sum);
}

int bar4(int *nums, int pos, int *busy, int bp)
{
  int i;

  busy[bp]=1;
  int *arr=ARRS[bp];
  BPS[pos]=bp;

  int right = nums[pos-1] % 100;
  if(pos==MAXN-1) {
    int left=nums[0]/100;

    int num=right*100+left;

    if(arr[num]==0) {
      BPS[pos]=0;
      return 0;
    }
    nums[pos]=num;
    dump(nums);
    return 1;
  }
  for(i=right*100;i<(1+right)*100;++i) {
    if(arr[i]==0) continue;
    nums[pos]=i;
    int j;
    for(j=1;j<MAXN;++j) {
      if(j==bp) continue;
      int stop=0;
      for(int k=0;k<MAXN;++k) if(BPS[k]==j) {stop=1;break;}
      if(stop)continue;
      if(bar4(nums, pos+1, busy, j)) return 1;
    }
  }
  BPS[pos]=0;
  return 0;
}

int bar3(int *nums, int pos)
{
  int i;
  int busy[MAXN]={0};
  busy[0]=1;
  BPS[0]=0;

  for(i=1000;i<10000;++i) {
    if(tri[i]==0) continue;
    nums[pos]=i;
    int j;
    for(j=1;j<MAXN;++j) {
      if(bar4(nums, pos+1, busy, j)) return 1;
    }
  }
  fprintf(stderr, "NOT FOUND\n");
  return 0;
}

int
main(int argc, char* argv[])
{
    filltri();
    fillsquare();
    fillpenta();
    fillhexa();
    fillhepta();
    fillocta();

    int NUMS[MAXN];
    bar3(NUMS, 0);

	return 0;
}

