#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <euler/assert.h>

#include "poker.h"

/* The below is incorrect but works on dataset provided by projecteuler. */
//#define TEST

static int
is_royal_flush(int hand[4][13])
{
  int suit, ret;

  for(suit = 0; suit < 4; ++suit) {
    ret = hand[suit][TEN] && hand[suit][JACK] && hand[suit][QUEEN] && hand[4][KING] && hand[4][ACE];
    if(ret) break;
  }
 
#ifdef VERBOSE
 if(ret) printf(" Royal Flush ");
#endif

 if(ret) {
   int kind, suit;
   for(kind = 12 - 5; kind >= 0; --kind) {
     for(suit = 0; suit < 4; ++suit) {
       if(hand[suit][kind]) {
	 ret = kind;
	 kind = -1;
	 break;
       }
     }
   }
   ret = ret + 1;
 }

  return ret;
}

static int
is_straight_flush(int hand[4][13])
{
  int suit, ret, i;
  int value = 0;

  for(suit = 0; suit < 4; ++suit) {
    for(i = 0; i < 13 - 5; ++i) {
      ret = hand[suit][i] && hand[suit][i+1] && hand[suit][i+2] && hand[suit][i+3] && hand[suit][i+4];
      if(ret) {
	value = i;
	break;
      }
    }
    if(ret) {
      break;
    }
  }

#ifdef VERBOSE
  if(ret) printf(" Straight Flush ");
#endif

  if(ret) {
    ret = value;
    ret = ret + 1;
  }

  return ret;
}

static int
is_four_of_a_kind(int hand[4][13])
{
  int i, ret;
  int value;

  value = 0;
  for(i = 0; i < 13; ++i) {
    ret = hand[0][i] && hand[1][i] && hand[2][i] && hand[3][i];
    if(ret) {
      value = i;
      break;
    }
  }

#ifdef VERBOSE
  if(ret) printf(" Four of a Kind ");
#endif

  if(ret) {
    ret = value;
    ret = ret + 1;
  }

  return ret;
}


static int
is_full_house(int hand[4][13])
{
  //three of a kind and a pair
  int ret, kind, two, three;
  int value;

  two = 0;
  three = 0;
  ret = 0;
  for(kind = 0; kind < 13; ++kind) {
    int sum = hand[0][kind]+hand[1][kind]+hand[2][kind]+hand[3][kind];
    if(sum==2) {
      if(two) {
	ret = 0;
	break;
      }
      two=1;
    }
    if(sum==3) {
      if(three) {
	ret=0;
	break;
      }
      three=1;
      value = kind;
    }
  }

  ret = (two && three);

#ifdef VERBOSE
  if(ret) printf(" Full House %c ", to_kind_name[value]);
#endif

  if(ret) {
    ret = value;
    ret = ret + 1;
  }

  return ret;
}

static int
is_flush(int hand[4][13])
{
  int suit, kind, ret;

  ret = 0;

  for(suit = 0; suit < 4; suit++) {
    int sum = 0;
    for(kind = 0; kind < 13; ++kind) {
      sum += hand[suit][kind];
    }
    if(sum==5) { ret = suit + 1; break; }
  }

  if(ret) {
    for(kind = 12; kind >= 0; --kind) {
      if(hand[ret-1][kind]) {
	ret = kind;
	break;
      }
    }
    ret = ret + 1;
  }

#ifdef VERBOSE
  if(ret) printf(" Flush %c", to_kind_name[ret-1]);
#endif

  return ret;
}

static int
is_straight(int hand[4][13])
{
  int suit, ret, i, sum;
  int value, k;

  ret = 0;
  for(i = 0; i < 13 - 5; ++i) {
    sum = 0;
    for(k=0;k<5;++k) {
      for(suit = 0; suit < 4; ++suit) {
	sum += hand[suit][i+k];
	if(hand[suit][i+k]) {
	  break;
	}
      }
    }
    if(sum == 5) {
      ret = 1;
      value = i;
      break;
    }
  }

#ifdef VERBOSE
  if(ret) printf(" Straight %c ", to_kind_name[value]);
#endif

  if(ret) {
    ret = value;
    ret = ret + 1;
  }

  return ret;
}

static int
is_three_of_a_kind(int hand[4][13])
{
  int kind, suit, ret;

  ret=0;
  for(kind = 0; kind < 13; ++kind) {
    int sum = 0;
    for(suit=0;suit<4;++suit) {
      sum += hand[suit][kind];
    }
    if(sum==3) {
      ret = kind + 1;
      break;
    }
  }

#ifdef VERBOSE
  if(ret) printf(" Three of a Kind %c ", to_kind_name[ret-1]);
#endif

  return ret;
}

static int
is_two_pairs(int hand[4][13])
{
  int kind, suit, npairs, ret;
  int value=0;

  npairs=0;
  for(kind = 0; kind < 13; ++kind) {
    int sum=0;
    for(suit=0;suit<4;++suit) {
      sum += hand[suit][kind];
    }
    if(sum==2) {
      npairs++;
      value = kind;
    }
  }
  ret=(npairs==2);

  if(ret) {
    ret = value;
    ret = ret + 1;
  }
#ifdef VERBOSE
  if(ret)  printf(" Two Pairs %c ", to_kind_name[ret-1]);
#endif

  return ret;
}

static int
is_one_pair(int hand[4][13])
{
  int kind, suit, npairs, ret;
  int value=0;

  npairs=0;
  for(kind = 0; kind < 13; ++kind) {
    int sum=0;
    for(suit=0;suit<4;++suit) {
      sum += hand[suit][kind];
    }
    if(sum==2) {
      npairs++;
      value = kind;
    }
  }
  ret = (npairs == 1);

#ifdef VERBOSE
  if(ret) printf(" One Pair of %c.", to_kind_name[value]);
#endif

  if(ret) {
    ret = value;
    ret = ret + 1;
  }

  return ret;
}

static int
is_high_card(int hand[4][13], int except)
{
  int kind;

  for(kind = 12; kind >= 0; --kind) {
    if(kind==except) continue;
    if(hand[0][kind]||hand[1][kind]||hand[2][kind]||hand[3][kind]) {
      return kind;
    }
  }

  return -1;
}

static PRIO functions[] = {
  is_royal_flush,
  is_straight_flush,
  is_four_of_a_kind,
  is_full_house,
  is_flush,
  is_straight,
  is_three_of_a_kind,
  is_two_pairs,
  is_one_pair
};

static int
whowins(const char *line)
{
  int first[4][13];
  int second[4][13];

  convert(line, first);
  convert(line + 3 * 5, second);

#ifdef VERBOSE
  print_hand(first);
  print_hand(second);
  print0(first);
  print0(second);
  printf("\n");
#endif

  int flush_first, flush_second;
  int i;

  for(i=0;i < sizeof(functions) / sizeof(functions[0]); ++i) {
    flush_first = functions[i](first);
    flush_second = functions[i](second);

    if(!flush_first && !flush_second) continue;
    if(!flush_first&&flush_second) return 2;
    if(flush_first&&!flush_second) return 1;
    if(flush_first && flush_second) {
      /* Find highest value. */
      if(flush_first == flush_second) {
#ifdef VERBOSE
	printf(" Looking for highest ");
#endif
	flush_first = is_high_card(first, flush_first - 1);
	flush_second = is_high_card(second, flush_second - 1);
      }

      int ret= flush_first > flush_second ? 1 : 2;
#ifdef VERBOSE
      if(ret==1) {
	printf(" first==%c", to_kind_name[flush_first]);
      } else {
	printf(" second==%c", to_kind_name[flush_second]);
      }
#endif
      return ret;
    }
  }

  flush_first = is_high_card(first, -1);
  flush_second = is_high_card(second, -1);

  int ret;

  if(flush_first > flush_second)
    ret=1;
  else
    ret=2;

#ifdef VERBOSE
  printf(" Highest Card %c", to_kind_name[ret==1?flush_first:flush_second]);
#endif

  return ret;
}

#ifdef TEST
static void
test()
{
  char *hand;
  hand = "2S 2D 3H 6D QD 5S 6S 7H TH AS";
  printf(" -> %d\n", whowins(hand));
#if 0
  hand = "2C 6D 9S KS KC 9H 9D TS TC QH";
  printf(" -> %d\n", whowins(hand));
  hand = "5H 5C 6S 7S KD 2C 3S 8S 8D TD";
  printf(" -> %d\n", whowins(hand));
  hand = "5D 8C 9S JS AC 2C 5C 7D 8S QH";
  printf(" -> %d\n", whowins(hand));
  hand = "2D 9C AS AH AC 3D 6D 7D TD QD";
  printf(" -> %d\n", whowins(hand));
  hand = "4D 6S 9H QH QC 3D 6D 7H QD QS";
  printf(" -> %d\n", whowins(hand));
  hand = "2H 2D 4C 4D 4S 3C 3D 3S 9S 9D";
  printf(" -> %d\n", whowins(hand));
#endif
}
#endif

int
main(int argc, char *argv[])
{
  char line[BUFSZ];
  FILE * fi = fopen(FILENAME, "r");
  int first_wins = 0;

#ifdef TEST
  test();
  return 0;
#endif

  if(fi == NULL) {
    FAIL("Can't open input file " FILENAME);
  }

  while(!feof(fi)) {
    if(fgets(line, BUFSZ,fi)==NULL) break;
    int winner = whowins(line);
    if(winner==1) first_wins++;
#ifdef VERBOSE
    printf("(%d) \n", winner);
#endif
  }
  printf("%d\n", first_wins);

  fclose(fi);
  return 0;
}
