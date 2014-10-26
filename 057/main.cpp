#include <stdio.h>

#include <euler/large.h>

int LSIZE;

struct pair
{
	struct large* top;
	struct large* bottom;

	pair(struct large* t, struct large* b)
		: top(large_clone(t))
		, bottom(large_clone(b))
	{
	}
	pair(struct large* t, const pair& other)
	{
		top = large_clone(t);
		large_mul(top, other.bottom);
		large_add(top, other.top);

		bottom = large_clone(other.bottom);
	}
	pair reverse()
	{
		return pair(large_clone(bottom), large_clone(top));
	}
	pair(const pair& other)
		: top(large_clone(other.top))
		, bottom(large_clone(other.bottom))
	{
	}
	const pair& operator=(const pair& other)
	{
		free();
		top = large_clone(other.top);
		bottom = large_clone(other.bottom);

		return *this;
	}
	void free()
	{
		large_free(top);
		large_free(bottom);
	}
	~pair()
	{
		free();
	}
};

static struct pair
foo(int depth, struct large* left)
{
	if(depth==1) {
		struct large* l = large_new(LSIZE);
		struct large* r = large_new(LSIZE);
		large_set(l, 1);
		large_set(r, 2);
		return pair(left, pair(l, r));
	}
	struct large* r = large_new(LSIZE);
	large_set(r, 2);
	return pair(left, foo(depth-1, r).reverse());
}

void
pair_print(const struct pair& pair)
{
	printf("[");
	large_print(pair.top);
	printf("/");
	large_print(pair.bottom);
	printf("]");
}

int main(int argc, char* argv[])
{
	int i;
	int count=0;

	LSIZE=10;
	for(i=1;i<=1000;++i) {
		struct large* uno = large_new(LSIZE);
		large_set(uno, 1);
		struct pair p = foo(i, uno);
		large_free(uno);
		if(i%100==0) {
			printf("%d (%d) /%d/ ", i, count, LSIZE);
			pair_print(p);
			printf("\n");
		}
		if(large_len(p.top)> LSIZE-8)
		{
			printf("ERR\n");
			return -1;
		}
		if(large_len(p.top) > large_len(p.bottom))
		{
			count++;
		}
		LSIZE = large_len(p.top) + 10;
	}
	printf("count=%d\n", count);

	return 0;
}

