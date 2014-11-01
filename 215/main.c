#include <stdio.h>

#define NROWS 3
#define NCOLS 9

static int
rows[NROWS][2];

static void
init()
{
  int i;

  for(i=0;i<NROWS;++i) rows[i][0]=rows[i][1]=0;
}

static int
W(int w, int h)
{
	return w+h;
}

int
main(int argc, char *argv[])
{
  init();
  printf("%d\n", W(9,3));
  return 0;
}
