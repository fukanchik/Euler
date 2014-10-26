#include <stdio.h>

#include <euler/config.h>
#include <euler/reverse.h>
#include <euler/palindrome.h>
#include <euler/large.h>

#define BEGIN 1
#define END 10000

int main(int argc, char *argv[])
{
	struct large* one = large_new(2);
	struct large *li = large_new(200);
	struct large *end = large_new(200);
	int lichrels=0;

	large_set(one, 1);

	large_set(li, BEGIN);
	large_set(end, END);
	for(;large_compare(li, end);)
	{
		int count;
		int flag=0;
		struct large *f = large_clone(li);

		for(count=0;count < 52; count++) {
			struct large* rev = large_reverse(f);
			struct large* val = large_clone(f);
			large_add(val, rev);

			if(!large_is_palindrome(val)) {
				large_free(f);
				f=val;
				continue;
			} else {	
				flag=1;
				break;
			}
		}
		if(!flag) {
			lichrels++;
		}
		large_add(li, one);
	}
	printf("%d\n", lichrels);

	return 0;
}

