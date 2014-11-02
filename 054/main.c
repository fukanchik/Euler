#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <euler/assert.h>

#include "poker.h"

static int
is_royal_flash(int hand[4][13])
{
  int suit, ret;

  for(suit = 0; suit < 4; ++suit) {
    ret = hand[suit][TEN] && hand[suit][JACK] && hand[suit][QUEEN] && hand[4][KING] && hand[4][ACE];
    if(ret) break;
  }
 
 if(ret) printf(" Royal Flash ");

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
 }

  return ret;
}

static int
is_straight_flash(int hand[4][13])
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

  if(ret) printf(" Straight Flash ");

  if(ret) {
    ret = value;
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
  if(ret) printf(" Four of a Kind ");
  if(ret) {
    ret = value;
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

  if(ret) ret = value;
  if(ret) printf(" Full House %c ", to_kind_name[ret]);

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
  }

  if(ret) printf(" Flush %c", to_kind_name[ret]);

  return ret;
}

static int
is_straight(int hand[4][13])
{
  
  int suit, ret, i, sum;

  ret = 0;
  for(i = 0; i < 13 - 5; ++i) {
    sum = 0;
    for(suit = 0; suit < 4; ++suit) {
      sum += hand[suit][i] + hand[suit][i+1] + hand[suit][i+2] + hand[suit][i+3] + hand[suit][i+4];
    }
    if(sum==5) {
      ret = 1;
      break;
    }
  }

  if(ret) printf(" Straight ");

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
      ret=1;
      break;
    }
  }

  if(ret) printf(" Three of a Kind ");

  return ret;
}

static int
is_two_pairs(int hand[4][13])
{
  int kind, suit, npairs, ret;

  npairs=0;
  for(kind = 0; kind < 13; ++kind) {
    int sum=0;
    for(suit=0;suit<4;++suit) {
      sum += hand[suit][kind];
    }
    if(sum==2) {
      npairs++;
    }
  }
  ret=(npairs==2);

  if(ret)  printf(" Two Pairs ");

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

  if(ret) ret = value;
  if(ret) printf(" One Pair of %c", to_kind_name[ret]);

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
  //printf("High Card");

  return -1;
}

static PRIO functions[] = {
  is_royal_flash,
  is_straight_flash,
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

  //print_hand(first);
  //print_hand(second);
  print0(first);
  print0(second);
  printf("\n");

  int flash_first, flash_second;
  int i;

  for(i=0;i < sizeof(functions) / sizeof(functions[0]); ++i) {
    flash_first = functions[i](first);
    flash_second = functions[i](second);

    if(!flash_first && !flash_second) continue;
    if(!flash_first&&flash_second) return 2;
    if(flash_first&&!flash_second) return 1;
    if(flash_first && flash_second) {
      /* Find highest value. */
      if(flash_first == flash_second) {
	printf(" Looking for highest ");
	flash_first = is_high_card(first, flash_first);
	flash_second = is_high_card(second, flash_second);
      }

      int ret= flash_first > flash_second ? 1 : 2;
      if(ret==1) {
	printf("%c", to_kind_name[flash_first]);
      } else {
	printf("%c", to_kind_name[flash_second]);
      }
      return ret;
    }
  }

  flash_first = is_high_card(first, -1);
  flash_second = is_high_card(second, -1);

  int ret;

  if(flash_first > flash_second)
    ret=1;
  else
    ret=2;

  printf(" Highest Card %c", to_kind_name[ret==1?flash_first:flash_second]);

  return ret;
}

static void
test()
{
  char *hand = "5H 5C 6S 7S KD 2C 3S 8S 8D TD";
  printf(" -> %d\n", whowins(hand));
  hand = "5D 8C 9S JS AC 2C 5C 7D 8S QH";
  printf(" -> %d\n", whowins(hand));
  hand = "2D 9C AS AH AC 3D 6D 7D TD QD";
  printf(" -> %d\n", whowins(hand));
  hand = "4D 6S 9H QH QC 3D 6D 7H QD QS";
  printf(" -> %d\n", whowins(hand));
  hand = "2H 2D 4C 4D 4S 3C 3D 3S 9S 9D";
  printf(" -> %d\n", whowins(hand));
}

int
main(int argc, char *argv[])
{
  char line[BUFSZ];
  FILE * fi = fopen(FILENAME, "r");
  int first_wins = 0;

  //test();
  //return 0;

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
