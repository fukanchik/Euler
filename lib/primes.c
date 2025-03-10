#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <euler/primes.h>
#include <euler/assert.h>

static void
primes_init(prime_list_t *list, u8 size)
{
	list->total  = size;
	list->count  = 0;
	list->primes = malloc(sizeof(u8) * size);
}

void
primes_free(prime_list_t *list)
{
	if (list)
	{
		memset(list->primes, 0, sizeof(u8) * list->total);
		free(list->primes);
		list->primes = NULL;
	}
}

void
primes_dump(prime_list_t *primes, const char *fname)
{
	int fd = open(fname, O_CREAT|O_TRUNC|O_WRONLY, 0666);
	if (fd==-1) FAIL("Can't open a file");
	write(fd, primes->primes, sizeof(u8)*primes->count);
	if (close(fd) != 0) FAIL("Can't close a file");
}

void
primes_load(prime_list_t *primes, const char *fname)
{
	struct stat st;
	int fd = open(fname, O_RDONLY, 0666);

	if (fd == -1) FAIL("Can't read a file");
	if (fstat(fd, &st) != 0) FAIL("Can' fstat()");

	primes->count = st.st_size / sizeof(u8);
	primes->total = primes->count;
	primes->primes = malloc(st.st_size);
	if (primes->primes == NULL)
		FAIL("Can't allocate mem for primes");
	if (read(fd, primes->primes, st.st_size) != st.st_size) FAIL("Can't read primes");

	if (close(fd) != 0)
		FAIL("Can't close a file");
}

void
primes_for_each(prime_list_t *list,
                bool (*f)(const prime_list_t *const, u8 prime, void *arg),
                void *arg)
{
	for (u8 i = 0; i < list->count; ++i)
	{
		if (f(list, list->primes[i], arg))
			break;
	}
}

void
primes_for_each_simple(prime_list_t *list,
                       bool (*f)(const prime_list_t *const, u8 prime))
{
	for (u8 i = 0; i < list->count; ++i)
	{
		if (f(list, list->primes[i]))
			break;
	}
}

void
primes_for_each_extra(u8 start, u8 end, prime_list_t *list,
                      bool (*f)(const prime_list_t *const, u8 position,
								u8 prime, void *arg),
                      void *arg)
{
	const u8 stop = MIN(end, list->count);

	for (u8 i = start; i < stop; ++i)
	{
		if (f(list, i, list->primes[i], arg))
			break;
	}
}

static void
primes_add(prime_list_t *list, u8 prime)
{
	if (list->total == list->count)
	{
		FAIL("Primes list is full!\n");
	}
	list->primes[list->count++] = prime;
}

static bool
primes_add_sieve(prime_list_t *list, u8 num)
{
	u8 half = sqrt(num) + 1;

	for (u8 i = 0; i < list->count && list->primes[i] < half; ++i)
		if ((num % list->primes[i]) == 0)
			return false;

	primes_add(list, num);

	return true;
}

void
primes_init_fill(prime_list_t *list, u8 size)
{
	primes_init(list, size / 2);
	primes_add(list, 2);

	for (u8 i = 3; i < size; ++i)
		primes_add_sieve(list, i);
}

bool
primes_is_prime(const prime_list_t *const list, u8 num)
{
	/* TODO: if num <= list->primes[max], then do binary search in the list. */
	u8 half = sqrt(num) + 1;

	if (num == 1) return 0;

	for (u8 i = 0; i < list->count && list->primes[i] < half; ++i)
		if ((num % list->primes[i]) == 0)
			return 0;

	return 1;
}
