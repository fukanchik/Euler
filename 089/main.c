#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <euler/assert.h>

#define INFILE "roman.txt" 

static char *LETTERS = "M CMD CDC XCL XLX IXV IVI ";
static int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

#define COUNT(x) (sizeof(x)/sizeof(x[0]))

static int
to_roman(int value, char *buf, int size)
{
  unsigned vpos = 0;
  int bpos = 0;

  while(vpos < COUNT(values)) {
    while(value >= values[vpos]) {
      value -= values[vpos];
      buf[bpos++]=LETTERS[vpos*2];
      int ch=LETTERS[vpos*2+1];
      if(ch!=' ') {
        buf[bpos++]=ch;
      }
      if(bpos > size) return 0;
    }
    vpos++;
  }
  return 1;
}

static int NN[1000]={['M'] = 1000, ['D'] = 500, ['C'] = 100, ['L'] = 50, ['X']=10, ['V']=5, ['I']=1};

static int
parse_roman(char *buf)
{
  int ret = 0;
  while(buf[0]!=0) {
    int v = NN[(unsigned char)buf[0]];
    int v2 = NN[(unsigned char)buf[1]];
    if(v==0) {
      printf("v=0\n");
      exit(0);
    }
    if(v >= v2) {
      ret += v;
    } else {
      ret -= v;
    }
    buf++;
  }

  return ret;
}

int
main(int c, char *v[])
{
  char buf[256];
  int lorig = 0;
  int lafter = 0;
  int num;
  FILE *fi = fopen(INFILE, "r");
  while(!feof(fi)) {
    memset(buf, 0, sizeof(buf));
    if(fgets(buf, 256, fi)==NULL) FAIL("Can't read "INFILE);
    if(buf[strlen(buf)-1]=='\n') {
      buf[strlen(buf)-1]=0;
    }
    lorig += strlen(buf);
    if(strlen(buf)==0) continue;
    num = parse_roman(buf);
    memset(buf, 0, sizeof(buf));
    to_roman(num, buf, 256);
    lafter += strlen(buf);
  }
  fclose(fi);
  printf("%d\n", lorig - lafter);

  return 0;
}

