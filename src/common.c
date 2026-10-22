#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

#define MAX_DECKS 8


void generate_standard_cards(Card* start_location) {
    int index = 0;
    for (int suit = 0; suit < 4; suit++) {
        for (int value = 2; value <= 14; value++) {
            start_location[index].value = value;
            start_location[index].suit = suit;

            index++;
        };
    };
}


void deck_init(Deck* deck, int amount) {
    deck->deck_amount = amount;
    deck->cards = malloc(52 * amount * sizeof(Card));
    deck->pointer = 0;

    for (int i = 0; i < amount; i++) {
        Card* insertion_point = &deck->cards[i * 52]; 
        
        generate_standard_cards(insertion_point);   
    }
}

void shuffle_deck(Deck* deck) {
    int total_cards = 52 * deck->deck_amount;
    for (int i = total_cards - 1; i >= 1; i--){
        int j = rand() % (i + 1);

        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}


