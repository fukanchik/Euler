#include <stdio.h>
#include <euler/assert.h>

#define FILENAME "p054_poker.txt"
#define BUFSZ 8192

typedef enum {
  TWO=0,
  THREE=1,
  FOUR=2,
  FIVE=3,
  SIX=4,
  SEVEN=5,
  EIGHT=6,
  NINE=7,
  TEN=8,
  JACK=9,
  QUEEN=10,
  KING=11,
  ACE=12
}  Hand;

int
rankings[];

static void
init_rankings()
{
  int i;

  /* Royal flush */
  rankings[0][TEN]=1;
  rankings[0][JACK]=1;
  rankings[0][QUEEN]=1;
  rankings[0][KING]=1;
  rankings[0][ACE]=1;

  /* Straight flush */
  for(i = 1; i < 2; i++) {
    
  }
}

static int
whowins(const char *line)
{
  const char *first = line;
  const char *second = line + 3*5;

  int royal
  
  printf("%s\n", second);
  return 1;
}

int
main(int argc, char *argv[])
{
  char line[BUFSZ];
  FILE * fi = fopen(FILENAME, "r");
  int first_wins = 0;

  if(fi == NULL) {
    FAIL("Can't open input file " FILENAME);
  }

  init_rankings();

  while(!feof(fi)) {
    if(fgets(line, BUFSZ,fi)==NULL) break;
    if(whowins(line)==1) first_wins++;
  }
  printf("%d\n", first_wins);

  fclose(fi);
  return 0;
}
