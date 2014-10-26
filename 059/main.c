#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define NAME "cipher1.txt"

struct finfo_t
{
	int freq;
	char ch;
};

struct finfo_t freqs[256];

static void
next(char *key, int p)
{
	if(p<0) return;
	key[p]++;
	if(key[p]>'z')
	{
		key[p]='a';
		next(key, p-1);
	}
}

static void
analize2(char *msg, int len)
{
	int i;
	char copy[4000];
	char key[3];
	key[0]='a';
	key[1]='a';
	key[2]='a';

	for(i=0;i<26*26*26;++i)
	{
		int j;

		memcpy(copy, msg, 4000);
		for(j=0;j<len;++j)
		{
			copy[j] ^= key[j%3];
		}
		if(strstr(copy, " the ")!=NULL) {
			int sum=0;
			int k;
			for(k=0;k<len;++k)
			{
				sum+=copy[k];
			}
			printf("Sum is: %d\nKey is:%c%c%c\nPlaintext is: %s\n",
				sum,
				key[0],
				key[1],
				key[2],
				copy);
		}
		
		next(key, 2);
	}
}

int
main(int argc, char* argv[])
{
	char cipher[4000];
	int ncipher;
	FILE *fi = fopen(NAME, "rb");
	if(fi==NULL)
	{
		fprintf(stderr, "Can't open %s\n", NAME);
		return -1;
	}
	ncipher=0;
	memset(cipher, 0, sizeof(cipher));
	while(!feof(fi))
	{
		int num=-1;
		int r=fscanf(fi, "%d,", &num);
		if(r==0||r==-1) break;
		cipher[ncipher++]=num;
	}
	analize2(cipher, ncipher);
	fclose(fi);
	return 0;
}
