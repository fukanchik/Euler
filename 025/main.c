#include <stdio.h>

#include <euler/large.h>

static void
fibo_next(struct large* f1, struct large* f2)
{
	large_add(f1, f2);
}

int
main(int argc, char* argv[])
{
	struct large* f1 = large_new(1500);
	struct large* f2 = large_new(1500);
	int i;

	large_set(f1, 1);
	large_set(f2, 1);

	for(i=0;i<10000;++i) {
		int l;
		fibo_next(f1, f2);
		l = large_len(f1);
		if(l>=1000) {
			printf("%d\n", i+3);
			break;
		}
		{
			struct large* t = f1;
			f1=f2;
			f2=t;
		}
	}

	return 0;
}

