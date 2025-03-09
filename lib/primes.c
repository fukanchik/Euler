#include <euler/config.h>
#include <euler/primes.h>
#include <euler/assert.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static void
primes_init(prime_list_t *list, int size)
{
	list->total  = size;
	list->count  = 0;
	list->primes = malloc(sizeof(int) * size);
}

void
primes_free(prime_list_t *list)
{
	if (list)
	{
		memset(list->primes, 0, sizeof(int) * list->total);
		free(list->primes);
		list->primes = NULL;
	}
}

void
primes_dump(prime_list_t *primes, const char *fname)
{
	int fd = open(fname, O_CREAT|O_TRUNC|O_WRONLY, 0666);
	if (fd==-1) FAIL("Can't open a file");
	write(fd, primes->primes, sizeof(int)*primes->count);
	if (close(fd) != 0) FAIL("Can't close a file");
}

void
primes_load(prime_list_t *primes, const char *fname)
{
	struct stat st;
	int fd = open(fname, O_RDONLY, 0666);

	if (fd == -1) FAIL("Can't read a file");
	if (fstat(fd, &st) != 0) FAIL("Can' fstat()");

	primes->count = st.st_size / sizeof(int);
	primes->total = primes->count;
	primes->primes = malloc(st.st_size);
	if (primes->primes == NULL) FAIL("Can't allocate mem for primes");
	if (read(fd, primes->primes, st.st_size) != st.st_size) FAIL("Can't read primes");

	if (close(fd) != 0) FAIL("Can't close a file");
}

void
primes_for_each(prime_list_t *list,
                int (*f)(const prime_list_t *const, int prime, void *arg),
                void *arg)
{
	int i;

	for (i = 0; i < list->count; ++i)
	{
		if (f(list, list->primes[i], arg)) break;
	}
}

void
primes_for_each_simple(prime_list_t *list,
                       int (*f)(const prime_list_t *const, int prime))
{
	int i;

	for (i = 0; i < list->count; ++i)
	{
		if (f(list, list->primes[i])) break;
	}
}

void
primes_for_each_extra(int start, int end, prime_list_t *list,
                      int (*f)(const prime_list_t *const, int position,
                               int prime, void *arg),
                      void *arg)
{
	int i;

	for (i = start; i < MIN(end, list->count); ++i)
	{
		if (f(list, i, list->primes[i], arg)) break;
	}
}

static void
primes_add(prime_list_t *list, int prime)
{
	if (list->total == list->count)
	{
		fprintf(stderr, "Primes list is full!\n");
		abort();
	}
	list->primes[list->count++] = prime;
}

static int
primes_add_sieve(prime_list_t *list, int num)
{
	int half = sqrt(num) + 1;
	int i;

	for (i = 0; i < list->count && list->primes[i] < half; ++i)
		if ((num % list->primes[i]) == 0) return 0;

	primes_add(list, num);

	return 1;
}

void
primes_init_fill(prime_list_t *list, int size)
{
	int i;

	primes_init(list, size / 2);
	primes_add(list, 2);

	for (i = 3; i < size; ++i) primes_add_sieve(list, i);
}

int
primes_is_prime(const prime_list_t *const list, int num)
{
	/* TODO: if num <= list->primes[max], then do binary search in the list. */
	int half = sqrt(num) + 1;
	int i;

	if (num == 1) return 0;
	for (i = 0; i < list->count && list->primes[i] < half; ++i)
		if ((num % list->primes[i]) == 0) return 0;

	return 1;
}
