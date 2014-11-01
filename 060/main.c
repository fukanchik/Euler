#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <euler/primes.h>
#include <euler/number.h>

#define EXTRA 0

#define NUMPRIMES 10000
prime_list_t primes;

static int*
build_graph()
{
  int i,j;
  int SIZE = primes.count * primes.count * sizeof(int);
  int *matrix = malloc(SIZE);

  /* Build connections. */
  for(i=0;i<primes.count;++i) {
    for(j=0;j<primes.count;++j) {
      int concat = num_concat(primes.primes[i], primes.primes[j]);
      int isprime = primes_is_prime(&primes, concat);
      if(isprime) {
	matrix[i*primes.count + j] = 1;
      } else {
	matrix[i*primes.count + j] = 0;
      }
    }
  }

  /* Remove when unidirectional. */
  for(i=0;i<primes.count;++i) {
    for(j=0;j<primes.count;++j) {
      matrix[i * primes.count + j] = matrix[i * primes.count + j] && matrix[i * primes.count + j] == matrix[j * primes.count + i];
    }
  }
  
  return matrix;
}

static void
print_row(int *row, int width)
{
  char *sep="";
  int i;

  printf("[");
  for(i=0;i<width;++i) {
    if(row[i] !=-1) {
      printf("%s%d", sep, primes.primes[row[i]]);
      sep = ", ";
    }
  }
  printf("]");
}

static int
row_len(int *row, int width)
{
  int len=0;
  int i;

  for(i=0;i<width;++i) {
    if(row[i]!=-1)len++;
  }
  return len;
}

static void
set_intersect(int *dest, int *src, int width)
{
  int i;

  for(i = 0; i < width; ++i) {
    if(dest[i]==i && src[i]==i) dest[i]=i;
    else dest[i]=-1;
  }
}

static void
set_union(int *dest, int vertex)
{
  dest[vertex]=vertex;
}

static void
set_diff(int *dest, int vertex)
{
  dest[vertex]=-1;
}

static void
neighbour(int *set, int *matrix, int width, int vertex)
{
  int i;

  for(i = 0; i < width; ++i) {
    if(matrix[vertex * width + i]) {
      set[i] = i;
    } else {
      set[i] = -1;
    }
  }
}

static int
is_empty(int *set, int width)
{
  int i;

  for(i=0;i<width;++i) {
    if(set[i] != -1) return 0;
  }
  return 1;
}

static void
bron_kerbosch_inner(int *matrix, int width, int *set_all, int *set_some, int *set_none)
{
  int SIZE = sizeof(int) * width;
  int i;

  if(is_empty(set_some, width) && is_empty(set_none, width)) {
    if(row_len(set_all, width)>4) {
      if(EXTRA) {
	printf("Returning ");
	print_row(set_all, width);
	printf("\n");
      }
      int sum=0;
      for(i=0;i<width;++i) sum+=primes.primes[set_all[i]];
      printf("%d\n", sum);
    }
    return;
  }

  int *dest = malloc(SIZE);
  int *new_all = malloc(SIZE);
  int *new_some = malloc(SIZE);
  int *new_none = malloc(SIZE);
  
  for(i = 0; i < width; ++i) {
    int v= set_some[i];
    if(v==-1)continue;

    memcpy(new_all, set_all, SIZE);
    set_union(new_all, v);

    memcpy(new_some, set_some, SIZE);
    neighbour(dest, matrix, width, v);
    set_intersect(new_some, dest, width);

    memcpy(new_none, set_none, SIZE);
    set_intersect(new_none, dest, width);

    bron_kerbosch_inner(matrix, width, new_all, new_some, new_none);

    set_diff(set_some, v);
    set_union(set_none, v);
  }
}

static void
bron_kerbosch(int *matrix, int width)
{
  int SIZE = sizeof(int) * width;
  int *set_all = malloc(SIZE);
  int *set_some = malloc(SIZE);
  int *set_none = malloc(SIZE);
  int i;

  for(i = 0; i < width; ++i) {
    set_all[i]=-1;
    set_some[i]=i;
    set_none[i]=-1;
  }

  bron_kerbosch_inner(matrix, width, set_all, set_some, set_none);
}

int
main(int argc, char *argv[])
{
  primes_init_fill(&primes, NUMPRIMES);

  int *matrix = build_graph();

  bron_kerbosch(matrix, primes.count);

  free(matrix);

  return 0;
}
