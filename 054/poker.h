#ifdef __poker_h_
#error "Double inclusion of poker.h"
#endif /* __poker_h_ */
#define __poker_h_

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

#define FILENAME "p054_poker.txt"
#define BUFSZ 8192

typedef int (*PRIO)(int hand[4][13]);

void print_hand(int hand[4][13]);
void print0(int hand[4][13]);

void convert(const char *hand, int out[4][13]);
Hand to_hand(char ch);
Suit to_suit(char ch);
extern char to_suit_name[4];
extern char to_kind_name[13];
