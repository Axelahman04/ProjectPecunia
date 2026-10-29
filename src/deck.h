#ifndef DECK_H
#define DECK_H

//Standard playing card
typedef struct {
    //2-14 value of card
    int value;

    //0-3 Suits, 0:Club, 1:Diamond, 2:Heart, 3:Spade 
    int suit;
} Card;

int card_color(Card* card);

typedef struct {
    // Amount of decks that are being used
    int deck_amount;

    // The list of all the cards
    Card *cards;

    // The pointer to where in the deck we are. 
    int pointer;
} Deck;

// 3. Prototyper för dina funktioner
void deck_init(Deck* deck, int amount);
void shuffle_deck(Deck* deck);
Card next_card(Deck* deck);
void display_card(Card* card);
int deck_contains(Card* card, int value);
#endif
