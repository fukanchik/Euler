#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#ifdef _WIN32
#include <process.h>
#endif

#include <euler/assert.h>

#define INFILE "words.txt"

#define QUOTE 1
#define WORD 2

static char **
read_words()
{
	char buf[20000];
	FILE* fi = fopen(INFILE, "rb");
	char **ret;
	int current;
	int state;
	int word_start=-1;
	int i;

	memset(buf, 0, sizeof(buf));
	if(fgets(buf, 20000, fi)==NULL) FAIL("Can't read from " INFILE);
	fclose(fi);
	ret = malloc(sizeof(char*)*2000);
	memset(ret, 0, sizeof(char*)*2000);
	current=0;
	state=QUOTE;
	for(i=0;buf[i];++i)
	{
		switch(state)
		{
		case QUOTE:
			if(buf[i]!='"')
			{
				fprintf(stderr, "Quote expected at %d\n", i);
				exit(1);
			}
			state=WORD;
			word_start=i+1;
			break;
		case WORD:
			if(buf[i]=='"')
			{
				int len = i - word_start;
				ret[current] = malloc(len + 1);
				memcpy(ret[current], buf+word_start, len);
				ret[current][len]=0;
				current++;
				i++;
				if(buf[i] && buf[i]!=',')
				{
					fprintf(stderr, "Comma expected at %d\n", i);
					exit(1);
				}
				state=QUOTE;
			}
			break;
		}
	}
	return ret;
}

static int
istriangle(int num)
{
	int i;

	for(i=1;;++i)
	{
		int tri = i*(i+1)/2;
		if(num==tri) return 1;
		if(tri > num) break;
	}
	return 0;
}

int
main(int argc, char *argv[])
{
	char **words = read_words();
	char **p;
	int count;

	for(count = 0, p=words;*p;++p)
	{
		char *w;
		int sum = 0;
		for(w=*p;*w;w++) sum+= *w - 'A' + 1;
		count += istriangle(sum);
		printf("%s %d\n", *p, sum);
	}
	printf("%d\n", count);

	for(p=words;*p;++p)
	{
		free(*p);
	}
	free(words);

	return 0;
}

