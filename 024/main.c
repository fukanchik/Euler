#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <process.h>
#endif

static char perms[11];
int count=1;

void
enlist(char *buf)
{
	if(count==1000000) {
		printf("%s\n", buf);
		exit(0);
	}
	count++;
}

void
permute(char *buf, int start, int n)
{
	enlist(buf);
	if(start < n)
	{
		int i, j;

		for(i = n - 2; i >= start; i--)
		{
			char t;
			for(j=i+1; j < n; j++)
			{
				char t = buf[i];
				buf[i] = buf[j];
				buf[j]=t;
				permute(buf, i+1, n);
			}
			t = buf[i];
			for(j=i; j < n-1;j++)
			{
				buf[j]=buf[j+1];
			}
			buf[n-1]=t;
		}
	}
}

int
main(int argc, char* argv[])
{
	strcpy(perms, "0123456789");
	/*strcpy(perms, "012");*/

	permute(perms, 0, 10);
	/*permute(perms, 0, 3);*/

	return 0;
}
