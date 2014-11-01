#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <euler/config.h>

#define BUFSZ 10000
#define DELTA 50

static char
buf[BUFSZ];

static ULL bufstart;
static ULL bufpos;

static void
move()
{
	ULL np = 0;
	ULL n = bufpos / 2;
	memcpy(buf+np, buf+n, DELTA);
	bufpos = np;
	bufstart += n;
}

static ULL
getpos(ULL N)
{
	ULL i;
	char strnum[DELTA];
	char *res;
	ULL occ = N;

	bufpos = 0;
	sprintf(strnum, ULLFMT, N);

	bufstart = 0;
	memset(buf, 0, sizeof(buf));

	for(i=1;i<20000000000ull;i++) {
		char num[DELTA];
		ULL len;

		sprintf(num, ULLFMT, i);

		len = strlen(num);
		memcpy(buf+bufpos, num, len + 1);

		res = strstr(buf, strnum);
		if(res != NULL) {
			ULL D = bufpos + len;
			occ--;
			if(occ == 0) {
				return bufstart + (res - buf) + 1;
			}
			bufstart += D;
			bufpos -= D;
			memcpy(buf, buf + D, DELTA);
		}

		bufpos += len;
		if(bufpos > BUFSZ - DELTA) {
			move();
		}
	}
	return 0;
}

int
main(int argc, char *argv[])
{
	ULL pos;
	pos = getpos(1);
	if(pos!=1) {
		fprintf(stderr, "1!=1 " ULLFMT "\n", pos);
//		return -1;
	}
	printf("\n");
	pos = getpos(3);
	if(pos != 37) {
		fprintf(stderr, "3!=37 " ULLFMT "\n", pos);
	}
	printf("\n");
	pos = getpos(5);
	if(pos != 81) {
		fprintf(stderr, "5!=81 " ULLFMT "\n", pos);
//		return -1;
	}
	printf("\n");
	pos = getpos(9);
	if(pos != 167) {
		fprintf(stderr, "9!=167 " ULLFMT "\n", pos);
	}
	printf("\n");
	pos = getpos(12);
	if(pos != 271) {
		fprintf(stderr, "12!=271 " ULLFMT "\n", pos);
//		return -1;
	}
	printf("\n");
	pos = getpos(7780);
	if(pos != 111111365) {
		fprintf(stderr, "7780 != 111111365 " ULLFMT "\n", pos);
	}
	printf("\n");

	fflush(stderr);

	ULL i;
	ULL po=3;
	for(i=0;i<13;++i) {
		fprintf(stderr, "[" ULLFMT "] " ULLFMT "\n", i+1, getpos(po));
		po *= 3;
		fflush(stderr);
	}
	return 0;
}


