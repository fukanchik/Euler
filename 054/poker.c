#include <stdio.h>
#include <string.h>

#include <euler/assert.h>

#include "poker.h"

Suit
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

Hand
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

void
convert(const char *hand, int out[4][13])
{
  memset(out, 0, sizeof(int) * 4 * 13);

  out[to_suit(hand[1])][to_hand(hand[0])] = 1;
  out[to_suit(hand[4])][to_hand(hand[3])] = 1;
  out[to_suit(hand[7])][to_hand(hand[6])] = 1;
  out[to_suit(hand[10])][to_hand(hand[9])] = 1;
  out[to_suit(hand[13])][to_hand(hand[12])] = 1;
}
