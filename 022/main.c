#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <io.h>
#include <process.h>
#endif
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
#include <malloc.h>
#include <string.h>

#include <euler/config.h>
#include <euler/assert.h>

#define INFILE "names.txt" 

static char**
read_names()
{
	char buf[50000];
	int fd;
	int i;
	char **ret;
	int sz=0;

	fd=open(INFILE, O_RDONLY|O_BINARY);
	if(fd == -1) FAIL("Can't open " INFILE);
	memset(buf, 0, sizeof(buf));
	if(read(fd, buf, 50000)==-1)FAIL("Can't read from "INFILE);
	close(fd);
	ret = (char**)malloc(50000*sizeof(char*));
	for(i=0;buf[i];++i) {
		char NAME[8192];
		memset(NAME, 0, sizeof(NAME));
		if(buf[i]!='"') {
			FAIL("Not \"");
		}
		i++;
		char*p=NAME;
		while(buf[i]!='"') {
			*p++=buf[i++];
		}
		i++;
		ret[sz++]=strdup(NAME);
		if(buf[i]!=','&&buf[i]!=0) {
			printf(">> '%s'\n", NAME);
			FAIL("Not ,");
		}
	}
	ret[sz]=NULL;
	return ret;
}

static int
count_names(char**n)
{
	int i;
	int count=0;

	for(i=0;n[i];++i)
	{
		count++;
	}
	return count;
}

static int
comp(const void* e1, const void* e2)
{
	char** p1 = (char**)e1;
	char** p2 = (char**)e2;
	return strcmp(*p1, *p2);
}

static int
calc(char*c)
{
	int sum=0;
	while(*c) {
		sum=sum+(*c-'A')+1;
		c++;
	}
	return sum;
}

int
main(int argc, char* argv[])
{
	char **names = read_names();
	int count = count_names(names);
	qsort(names, count, sizeof(char*), comp);
	char**p=names;
	ULL total=0;
	int pos=1;
	while(*p) {
		total+=calc(*p)*pos;
		pos++;
		p++;
	}
	printf(ULLFMT"\n", total);

	return 0;
}

