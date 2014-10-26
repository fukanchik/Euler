#include <stdio.h>

#include <euler/primes.h>

#define NUM 30000

struct prime_list_t primes;

int cache[NUM];

int
diagonals(int sz)
{
	int diag[4];

	if(sz == 1) return 0;
	if(cache[sz]!=-1) return cache[sz];

	diag[0]=sz*sz;
	diag[1]=diag[0]-sz+1;
	diag[2]=diag[1]-sz+1;
	diag[3]=diag[2]-sz+1;

	diag[0] = primes_is_prime(&primes, diag[0]);
	diag[1] = primes_is_prime(&primes, diag[1]);
	diag[2] = primes_is_prime(&primes, diag[2]);
	diag[3] = primes_is_prime(&primes, diag[3]);

	int add = diag[0]+diag[1]+diag[2]+diag[3];
	int add2 = add + diagonals(sz-2);

	cache[sz]=add2;

	return add2;
}

int main(int argc, char *argv[])
{
	int sz;

	primes_init_fill(&primes, 1000000);
	for(sz=0;sz<NUM;++sz){cache[sz]=-1;}

	for(sz=3;sz<NUM;sz+=2) {
		int total = 2*sz-1;
		int diag = diagonals(sz);
		double ratio = diag*100.0/total;
		if(ratio < 10.0) {
		printf("%d->%d/%d %f%%\n", sz, diag, total, ratio);
			break;
		}
	}

	return 0;
}

