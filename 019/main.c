#include <stdio.h>
#include <time.h>
#include <memory.h>

struct date
{
	int year;
	int month;
	int day;
	int weekday;
};

static int
isleap(int year)
{
	if((year%400)==0)
		return 1;
	if((year%100)==0)
		return 0;
	if((year%4)==0)
		return 1;
	return 0;
}

static int
daysinmonth(int year, int month)
{
	int days[]={-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(month==2 && isleap(year))
		return 29;
	return days[month];
}

static void
date_inc(struct date* date)
{
	int dim = daysinmonth(date->year, date->month);
	int nextday = date->day + 1;

	date->weekday = (date->weekday+1)%7;
	if(nextday <= dim) {
		date->day = nextday;
		return;
	}
	date->day=1;
	date->month++;
	if(date->month>12) {
		date->month=1;
		date->year++;
	}
}

static int
date_eq(struct date* d1, struct date* d2)
{
	return d1->year==d2->year && d1->month == d2->month && d1->day==d2->day;
}

int main(int argc, char* argv[])
{
	struct date start = {1900, 1, 1, 0};
	struct date end = {2000, 12, 31, 6};

	int count = 0;
	do {
		date_inc(&start);
		if((start.year>1900) && (start.day==1) && (start.weekday==6)) {
			count++;
		}
	} while(!date_eq(&start, &end));
	printf("%d\n", count);

	return 0;
}
