#include <stdio.h>
#include <string.h>

/*directly from wikipedia*/
static const char* __names[]={
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
	"ten",
	"eleven",
	"twelve",
	"thirteen",
	"fourteen",
	"fifteen",
	"sixteen",
	"seventeen",
	"eighteen",
	"nineteen",
	"twenty"
};

static const char* __decs[]={
	"",
	"",
	"twenty",
	"thirty",
	"forty",
	"fifty",
	"sixty",
	"seventy",
	"eighty",
	"ninety"
};

static void
number_as_word(int num, char* buf)
{
	buf[0]=0;

	if(num == 1000) {
		strncpy(buf, "one thousand", 8192);
		return;
	}
	if(num >= 100)
	{
		int d = (num % 1000) / 100;
		int r = num % 100;
		number_as_word(d, buf);
		strncat(buf, " hundred", 8192);
		if(r>0)
		{
			char bufr[8192];
			strncat(buf, " and ", 8192);
			number_as_word(r, bufr);
			strncat(buf, bufr, 8192);
		}
		return;
	}
	if (num > 20)
	{
		int d = (num % 100)/10;
		int r = num % 10;

		strncat(buf, __decs[d], 8192);
		if(r>0)
		{
			char bufr[256];
			strncat(buf, "-", 8192);
			number_as_word(r, bufr);
			strncat(buf, bufr, 8192);
		}
		return;
	}
	if(0 < num && num<=20)
	{
		strncat(buf, __names[num], 8192);
		return;
	}

}

static int
count(char * buf)
{
	int l = strlen(buf);
	int c, i;

	for(c=0, i=0;i<l;++i)
	{
		if(buf[i]>='a' && buf[i] <='z')c++;
	}
	return c;
}

int
main(int argc, char* argv[])
{
	int i;
	int total;

	for(total=0, i=1;i<=1000;++i)
	{
		char buf[8192];

		number_as_word(i, buf);
		total += count(buf);
	}
	printf("%d\n", total);
	return 0;
}
