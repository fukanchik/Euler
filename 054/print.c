#include <stdio.h>

#include "poker.h"

char to_suit_name[4]={'S', 'H', 'D', 'C'};
char to_kind_name[13]={'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

void
print_hand(int hand[4][13])
{
  int kind, suit;

  printf(" 23456789TJQKA\n");
  for(suit=0;suit<4;++suit) {
    printf("%c", to_suit_name[suit]);
    for(kind = 0; kind < 13; kind++) {
      printf("%d", hand[suit][kind]);
    }
    printf("\n");
  }

  printf("\n");
}

void
print0(int hand[4][13])
{
  int kind, suit;
  char *sep="";

  printf("[");
  for(kind = 0; kind < 13; ++kind) {
    for(suit = 0; suit < 4; ++suit) {
      if(hand[suit][kind]) {
	printf("%s%c%c", sep, to_kind_name[kind], to_suit_name[suit]);
	sep=" ";
      }
    }
  }
  printf("]");
}
