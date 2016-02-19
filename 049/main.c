#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <euler/assert.h>
#include <euler/config.h>
#include <euler/number.h>

#define PRIMESINPUT "primes1.txt"

#define NPRIM 1000000
#define MAGIC 3330

ULL primes[NPRIM];

static void
read_primes()
{
  int i;
  FILE *fi = fopen(PRIMESINPUT, "r");

  if(fi==NULL) {
    fprintf(stderr, "Can't find primes!\n");
    exit(-1);
  }

  for(i=0;!feof(fi) && i < NPRIM;++i) {
    if(fscanf(fi, ULLFMT , primes+i) != 1) FAIL("Corrupted primes input file " PRIMESINPUT);
  }
  printf(ULLFMT "\n", primes[NPRIM-1]);
  fclose(fi);
}

static int
isprime(ULL num)
{
  int i;

  for(i=0;i < NPRIM;++i) {
    if(primes[i]==num)
      return 1;
    if(primes[i] > num)
      return 0;
  }
  return 0;
}

static int
hasprop(int n)
{
  int n1 = n;
  int n2 = n1 + MAGIC;
  int n3 = n2 + MAGIC;

  if(!isprime(n1))
    return 0;
  if(!isprime(n2))
    return 0;
  if(!isprime(n3))
    return 0;
  if(!is_permutation(n1, n2))
    return 0;
  if(!is_permutation(n1, n3))
    return 0;
  if(!is_permutation(n2, n3))
    return 0;
  return 1;
}

int
main(int c, char *v[])
{
  int i;

  read_primes();

  if(!is_permutation(1487, 4817)) {
    fprintf(stderr, "!isperm(1487, 4817)\n");
    return -1;
  }
  if(is_permutation(1487, 4816)) {
    fprintf(stderr, "isperm(1487, 4816)\n");
    return -1;
  }

  for(i=1000;i<10000;++i) {
    if(hasprop(i)) {
      printf("%d %d %d\n", i, i+MAGIC, i+MAGIC+MAGIC);
    }
  }

  return 0;
}
