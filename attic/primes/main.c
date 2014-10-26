#include <stdio.h>
#include <stdlib.h>

#define NPRIMES 1000000

static int primes[NPRIMES];

static void
read_primes()
{
	int i;
	FILE *fi = fopen("primes.txt", "r");
	if(fi==NULL) {
		fprintf(stderr, "Can't read primes.\n");
		exit(1);
	}

	for(i=0;i<NPRIMES;++i) {
		fscanf(fi, "%d", &primes[i]);
	}

	fclose(fi);
}

static int
is_prime(int num)
{
	int i;

	for(i=0;i<NPRIMES;++i) {
		if(primes[i]==num) return 1;
	}
	return 0;
}

int
main(int argc, char* argv[])
{
	read_primes();
	return 0;
}

