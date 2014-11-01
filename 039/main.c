#include <stdio.h>

#include <euler/assert.h>

#define max(x,y) (x>y?x:y)

static int
istri(int a, int b, int c)
{
	int ret;
	int h = max(a, max(b,c));
	int s1, s2;
	if(h==a)
	{s1=b;s2=c;} else if(h==b)
	{s1=a;s2=c;} else if(h==c)
	{s1=a;s2=b;} else { FAIL("Impossible"); s1=s2=0;}

	ret = h * h == s1 * s1 + s2 * s2;

	return ret;
}

int I[1000];
int J[1000];
int K[1000];
int c;

static int
find(int n)
{
	int i;

	for(i=0;i<c;++i)
	{
		if(I[i]==n||J[i]==n||K[i]==n)
			return 1;
	}
	return 0;
}

static int
count(int p)
{
	int i,j, k;
	c=0;
	for(i = 1; i < p; ++i)
	{
		for(j=1;j<p-i;++j)
		{
			k = p - i - j;
			if(istri(i,j,k) && !find(i))
			{
				I[c]=i;
				J[c]=j;
				K[c]=k;
				c++;
			}
		}
	}
	return c;
}

int
main(int argc, char *argv[])
{
	int p;
	int max=0;
	int n;

	for(p=1;p<=1000;p++)
	{
		int c = count(p);
		if(c>max){max=c;n=p;}
	}
	printf("%d\n", n);

	return 0;
}
