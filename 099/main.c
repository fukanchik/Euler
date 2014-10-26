#include <stdio.h>
#include <math.h>

#include <euler/assert.h>

#define INPUT "p099_base_exp.txt"

/*
 * b1^e1=x1 ??? b2^e2=x2
 * log_b(x)=e
 * log_10(x)/log_10(b)=e
 * log_10(x)=e*log_10(b)
 * ...log10(x1)=e1*log_10(b1) ??? log_10(x2)=e2*log_10(b2)
 * e1*log10(b1) ??? e2*log10(b2)
 */
int
main(int argc, char *argv[])
{
	FILE *fi;
	double maxlog = 0.0f;
	int maxpos = -1;
	int ln;

	fi = fopen(INPUT, "r");
	if(!fi) FAIL("Can't open " INPUT);
	for(ln=1;!feof(fi); ln++) {
		int base, exp;
		double curlog;
		if(fscanf(fi, "%d,%d\n", &base, &exp) != 2) FAIL(INPUT " is corrupted.");
		curlog=exp*log10(base);
		if(curlog>maxlog) {
			maxlog = curlog;
			maxpos = ln;
		}
	}
	printf("%d\n", maxpos);
	fclose(fi);
	return 0;
}

