#include <stdio.h>

#include <euler/config.h>
#include <euler/assert.h>

static ULL
powi(ULL b, ULL e)
{
	ULL i, ret;

	ret=1;
	for(i=0;i<e;++i) {
		ret *= b;
	}
	return ret;
}

static ULL
numlen(ULL i)
{
	ULL len=0;

	while(i>0) {
		len++;
		i/=10;
	}
	return len;
}

int main(int argc, char *argv[])
{
	ULL i, j;

	if(numlen(1)!=1)FAIL("1");
	if(numlen(42)!=2)FAIL("42");
	if(numlen(221)!=3)FAIL("221");
	if(numlen(7770)!=4)FAIL("7770");

	if(powi(2, 3) != 8) FAIL("2^3");
	if(powi(1, 10) != 1) FAIL("1^10");
	if(powi(3, 3) != 27) FAIL("3^3");
	if(powi(12, 2) != 144) FAIL("12^2");

	if(powi(7, 5) != 16807) FAIL("7^5");
	
	for(i=2;i<100;++i) {
		for(j=0;;++j) {
			ULL num, nlen;
			num = powi(j, i);
			nlen=numlen(num);
			if(nlen > i) break;
			if(nlen == i) printf(ULLFMT "^" ULLFMT "=" ULLFMT "\n", j, i, num);
		}
	}
	return 0;
}

