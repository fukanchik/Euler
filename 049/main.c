#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <euler/assert.h>

#define PRIMESINPUT "primes1.txt"

#define NPRIM 1000000
#define UINT unsigned int
#define MAGIC 3330

UINT primes[NPRIM];

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
    if(fscanf(fi, "%u", primes+i) != 1) FAIL("Corrupted primes input file " PRIMESINPUT);
  }
  printf("%d\n", primes[NPRIM-1]);
  fclose(fi);
}

static int
ispermutation(int n1, int n2)
{
  int nums1[10], nums2[10];

  memset(nums1, 0, sizeof(nums1));
  memset(nums2, 0, sizeof(nums2));

  while(n1) {
    int digit = n1 % 10;
    n1 /= 10;
    nums1[digit]++;
  }
  while(n2) {
    int digit = n2 % 10;
    n2 /= 10;
    nums2[digit]++;
  }
  return !memcmp(nums1, nums2, sizeof(nums1));
}

static int
isprime(int num)
{
  int i;

  for(i=0;i<NPRIM;++i) {
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
  if(!ispermutation(n1, n2))
    return 0;
  if(!ispermutation(n1, n3))
    return 0;
  if(!ispermutation(n2, n3))
    return 0;
  return 1;
}

int
main(int c, char *v[])
{
  int i;

  read_primes();

  if(!ispermutation(1487, 4817)) {
    fprintf(stderr, "!isperm(1487, 4817)\n");
    return -1;
  }
  if(ispermutation(1487, 4816)) {
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
