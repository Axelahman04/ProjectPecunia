#include <stdio.h>
#include <stdlib.h>

#define MAX_DECKS 8

//Standard playing card
typedef struct {
    //2-14 value of card
    int value;

    //0-3 Suits, 0:Club, 1:Diamond, 2:Heart, 3:Spade 
    int suit;
} Card;


typedef struct {
    int deck_amount1;
    Card *cards;
    int top_pointer;
} Deck;

void init(Deck* deck) {

}



