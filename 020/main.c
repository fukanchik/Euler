#include <stdio.h>
#include <string.h>

#include <euler/large.h>

static char num[]="93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000";

static void
test_large()
{
	struct large *n1 = large_new(10);
	struct large *n2 = large_new(10);

	n1->buffer[0]=0;
	n2->buffer[0]=3;

	large_free(n1);
	large_free(n2);
	n1 = large_new(1000);
	n2 = large_new(1000);
	n1->buffer[0]=1;
	n1->buffer[1]=0;
	n2->buffer[0]=2;
	n2->buffer[1]=0;
}

static struct large*
fact100()
{
	struct large* ret = large_new(600);
	struct large* m = large_new(10);
	int i;

	ret->buffer[0]=1;
	for(i=1;i<=100;++i)
	{
		large_set(m, i);
		large_mul(ret, m);
	}

	large_free(m);

	return ret;
}

int main(int argc, char* argv[])
{
	int sum = 0;
	int sum2=0;
	int i;
	int size=strlen(num);

	test_large();

	for(i=0;i<size;++i)
	{
		sum = sum + (num[i]-'0');
	}
	printf("sum=%d\n", sum);
	struct large* f100 = fact100();

	for(i=0;i<f100->capacity;++i)
	{
		sum2+=f100->buffer[i];
	}
	printf("sum2=%d\n", sum2);
	return 0;
}

