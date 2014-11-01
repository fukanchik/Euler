#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef enum {
  Spades=0,
  Hearts=1,
  Diamonds=2,
  Clubs=3
} Suit;

static Suit
to_suit(char ch)
{
  switch(ch) {
  case 'S':
    return Spades;
  case 'H':
    return Hearts;
  case 'D':
    return Diamonds;
  case 'C':
    return Clubs;
  }
  FAIL("Not a suit %c", ch);
  return -1;
}

static Hand
to_hand(char ch)
{
  switch(ch) {
  case '2':
    return TWO;
  case '3':
    return THREE;
  case '4':
    return FOUR;
  case '5':
    return FIVE;
  case '6':
    return SIX;
  case '7':
    return SEVEN;
  case '8':
    return EIGHT;
  case '9':
    return NINE;
  case 'T':
    return TEN;
  case 'J':
    return JACK;
  case 'Q':
    return QUEEN;
  case 'K':
    return KING;
  case 'A':
    return ACE;
  }
  FAIL("Unknown type %c", ch);
  return -1;
}

static int
sort_hand(const void *v1, const void *v2)
{
  const int *p1 = (const int*)v1;
  const int *p2 = (const int*)v2;

  return *p1 - *p2;
}

static void
convert(const char *hand, int out[10])
{
  out[0] = to_hand(hand[0]);
  out[1] = to_suit(hand[1]);
  out[2] = to_hand(hand[3]);
  out[3] = to_suit(hand[4]);
  out[4] = to_hand(hand[6]);
  out[5] = to_suit(hand[7]);
  out[6] = to_hand(hand[9]);
  out[7] = to_suit(hand[10]);
  out[8] = to_hand(hand[12]);
  out[9] = to_suit(hand[13]);
}

static void
print_hand(int *hand)
{
  int i;

  for(i = 0; i < 10; i += 2) {
    printf("%d/%d ", hand[i+0], hand[i+1]);
  }
  printf("\n");
}

static int
is_royal_flash(int *hand)
{
  if(!((hand[1]==hand[3])&&(hand[3]==hand[5])&&(hand[3]==hand[7])&&(hand[3]==hand[9]))) {
    return 0;
  }
  int ret = hand[0]==TEN && hand[2]==JACK && hand[4]==QUEEN && hand[6]==KING && hand[8]==ACE;
  if(ret)printf(" Royal Flash ");

  return ret;
}

static int
is_straight_flash(int *hand)
{
  if(!((hand[1]==hand[3])&&(hand[3]==hand[5])&&(hand[3]==hand[7])&&(hand[3]==hand[9]))) {
    return 0;
  }
  int ret = (hand[8]-hand[6])==1 && (hand[6]-hand[4])==1 && (hand[4]-hand[2])==1 && (hand[2]-hand[0])==1;
  if(ret) printf("Straight Flash");

  return ret;
}

static int
is_four_of_a_kind(int *hand)
{
  int sum;
  sum += (hand[2]==hand[0]);
  sum += (hand[4]==hand[0]);
  sum += (hand[6]==hand[0]);
  sum += (hand[8]==hand[0]);

  sum += (hand[4]==hand[2]);
  sum += (hand[6]==hand[2]);
  sum += (hand[8]==hand[2]);

  sum += (hand[6]==hand[4]);
  sum += (hand[8]==hand[4]);

  sum += (hand[8]==hand[6]);

  int ret = sum==4;
  if(ret) printf("Four of a Kind");

  return ret;
}


static int
is_full_house(int *hand)
{
  //three of a kind and a pair
  int temp[13];
  int two=0;
  int three=0;
  int i;

  memset(temp, 0, sizeof(int) * 13);
  for(i = 0; i < 5; i++) {
    temp[hand[i*2]]++;
  }
  for(i = 0; i < 13; i++) {
    if(temp[i]==2) {
      if(two) return 0;
      two=1;
    }
    if(temp[i]==3) {
      if(three) return 0;
      three=1;
    }
  }
  int ret= two && three;
  if(ret) printf("Full House");

  return ret;
}

static int
is_flush(int *hand)
{
  if(!((hand[1]==hand[3])&&(hand[3]==hand[5])&&(hand[3]==hand[7])&&(hand[3]==hand[9]))) {
    return 0;
  }
  printf("Flush");
  return 1;
}

static int
is_straight(int *hand)
{
  int ret = (hand[8]-hand[6])==1 && (hand[6]-hand[4])==1 && (hand[4]-hand[2])==1 && (hand[2]-hand[0])==1;
  if(ret) printf("Straight");

  return ret;
}

static int
is_three_of_a_kind(int *hand)
{
  int sum;
  sum += (hand[2]==hand[0]);
  sum += (hand[4]==hand[0]);
  sum += (hand[6]==hand[0]);
  sum += (hand[8]==hand[0]);

  sum += (hand[4]==hand[2]);
  sum += (hand[6]==hand[2]);
  sum += (hand[8]==hand[2]);

  sum += (hand[6]==hand[4]);
  sum += (hand[8]==hand[4]);

  sum += (hand[8]==hand[6]);

  int ret = sum == 3;
  if(ret) printf("Three of a Kind");

  return ret;
}

static int
is_two_pairs(int *hand)
{
  //two different pairs
  int temp[4][13];
  int sum[4];
  int i;

  memset(temp, 0, sizeof(int) * 13 * 4);
  memset(sum, 0, sizeof(int) * 4);

  for(i = 0; i < 5; i++) {
    temp[hand[i*2+1]][hand[i*2]]++;
  }

  printf("Two Pairs");

  return 1;
}

static int
is_one_pair(int *hand)
{
  printf("One Pair");

  return 1;
}

static int
is_high_card(int *hand)
{
  printf("High Card");

  return 1;
}

static int
whowins(const char *line)
{
  int first[10];
  int second[10];

  convert(line, first);
  convert(line + 3 * 5, second);

  qsort(first, 5, sizeof(int)*2, sort_hand);
  qsort(second, 5, sizeof(int)*2, sort_hand);

  /* Royal flash */
  int flash_first = is_royal_flash(first);
  int flash_second = is_royal_flash(second);

  if(flash_first&&!flash_second) return 1;
  if(!flash_first&&flash_second) return 2;

  /* Straight flash */
  flash_first = is_straight_flash(first);
  flash_second = is_straight_flash(second);

  if(flash_first&&!flash_second) return 1;
  if(!flash_first&&flash_second) return 2;

  flash_first = is_four_of_a_kind(first);
  flash_second = is_four_of_a_kind(second);

  if(flash_first&&!flash_second) return 1;
  if(!flash_first&&flash_second) return 2;

  flash_first = is_full_house(first);
  flash_second = is_full_house(second);

  if(flash_first&&!flash_second) return 1;
  if(!flash_first&&flash_second) return 2;

  flash_first = is_flush(first);
  flash_second = is_flush(second);

  if(flash_first&&!flash_second) return 1;
  if(!flash_first&&flash_second) return 2;

  flash_first = is_straight(first);
  flash_second = is_straight(second);

  if(flash_first&&!flash_second) return 1;
  if(!flash_first&&flash_second) return 2;

  flash_first = is_three_of_a_kind(first);
  flash_second = is_three_of_a_kind(second);

  if(flash_first&&!flash_second) return 1;
  if(!flash_first&&flash_second) return 2;

  flash_first = is_two_pairs(first);
  flash_second = is_two_pairs(second);

  if(flash_first&&!flash_second) return 1;
  if(!flash_first&&flash_second) return 2;

  flash_first = is_one_pair(first);
  flash_second = is_one_pair(second);

  if(flash_first&&!flash_second) return 1;
  if(!flash_first&&flash_second) return 2;

  flash_first = is_high_card(first);
  flash_second = is_high_card(second);

  if(flash_first&&!flash_second) return 1;
  if(!flash_first&&flash_second) return 2;

  print_hand(first);

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

  while(!feof(fi)) {
    if(fgets(line, BUFSZ,fi)==NULL) break;
    if(whowins(line)==1) first_wins++;
  }
  printf("%d\n", first_wins);

  fclose(fi);
  return 0;
}
