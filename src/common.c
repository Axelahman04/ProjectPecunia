#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

#define MAX_DECKS 8


int card_color(Card* card) {
    switch(card->suit) {
        case 0: 
            return 1;
        case 1:
            return 0;
        case 2:
            return 0;
        case 3:
            return 1;
    }
}

void display_card(Card* card) {
    printf("The card is %d of %d\n", card->value, card->suit);
}


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

Card next_card(Deck* deck) {
    Card top_card = deck->cards[deck->pointer];
    deck->pointer++;

    return top_card;
}

int deck_contains(Card *deck, int value) {
    int size = sizeof(*deck) / sizeof(Card);
    
    for (int i = 0; i < size; i++) {
        if (deck[i].value == value)
            return 1;
    }

    return 0;
}


int get_number_input(int min, int max) {
    int input;

    if (scanf("%d", &input) == 1) {
        if (input >= min && input <= max) {
            return input;
        } else {
            printf("Amount needs to be between %d and %d\n", min, max);
        }
    } else {
        printf("Invalid input. Please enter a number.\n");

        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}


int clamp(int value, int min, int max) {
    if (value < min)
        return min;
    else if (value > max)
        return max;
    
    return value;
}