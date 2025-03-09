#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <euler/config.h>

#define BUFSZ 10000
#define DELTA 50

static char
buf[BUFSZ];

static u8 bufstart;
static u8 bufpos;

static void
move(void)
{
	u8 np = 0;
	u8 n = bufpos / 2;
	memcpy(buf+np, buf+n, DELTA);
	bufpos = np;
	bufstart += n;
}

static u8
getpos(u8 N)
{
	u8 i;
	char strnum[DELTA];
	char *res;
	u8 occ = N;

	bufpos = 0;
	sprintf(strnum, "%llu", N);

	bufstart = 0;
	memset(buf, 0, sizeof(buf));

	for(i=1;i<20000000000ull;i++) {
		char num[DELTA];
		u8 len;

		sprintf(num, "%llu", i);

		len = strlen(num);
		memcpy(buf+bufpos, num, len + 1);

		res = strstr(buf, strnum);
		if(res != NULL) {
			u8 D = bufpos + len;
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
	u8 pos;
	pos = getpos(1);
	if(pos!=1) {
		fprintf(stderr, "1!=1 %llu\n", pos);
//		return -1;
	}
	printf("\n");
	pos = getpos(3);
	if(pos != 37) {
		fprintf(stderr, "3!=37 %llu\n", pos);
	}
	printf("\n");
	pos = getpos(5);
	if(pos != 81) {
		fprintf(stderr, "5!=81 %llu\n", pos);
//		return -1;
	}
	printf("\n");
	pos = getpos(9);
	if(pos != 167) {
		fprintf(stderr, "9!=167 %llu\n", pos);
	}
	printf("\n");
	pos = getpos(12);
	if(pos != 271) {
		fprintf(stderr, "12!=271 %llu\n", pos);
//		return -1;
	}
	printf("\n");
	pos = getpos(7780);
	if(pos != 111111365) {
		fprintf(stderr, "7780 != 111111365 %llu\n", pos);
	}
	printf("\n");

	fflush(stderr);

	u8 i;
	u8 po = 3;
	for(i=0;i<13;++i) {
		fprintf(stderr, "[%llu] %llu\n", i+1, getpos(po));
		po *= 3;
		fflush(stderr);
	}
	return 0;
}
