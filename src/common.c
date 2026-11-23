#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

#define MAX_DECKS 8

volatile int *btn_pointer = (volatile int*)0x040000d0;
volatile int btn_pressed = 0;

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
    deck->deck_amount = 1;
    deck->pointer = 0;

    for (int i = 0; i < 1; i++) {
        Card* insertion_point = &deck->cards[i * 52]; 
        
        generate_standard_cards(insertion_point);   
    }
}

void shuffle_deck(Deck* deck) {
    int total_cards = 52 * deck->deck_amount;
    for (int i = total_cards - 1; i >= 1; i--){
        int j = my_rand() % (i + 1);

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

}


int clamp(int value, int min, int max) {
    if (value < min)
        return min;
    else if (value > max)
        return max;
    
    return value;
}

void enable_input() {
    *(btn_pointer + 3) = 1;
    *(btn_pointer + 2) = 1;
}

int get_input() {

    //Wait for input
    while(btn_pressed = 0){}

    //Check when btn is first pressed down
    int start = get_cycles();

    //True as long as btn is down
    while (*btn_pointer & 1){
        //Determine if button is pressed for sufficient time for long press
        if((get_cycles() - start) > 1200000){

            while(btn_pressed & 1){}
            btn_pressed = 0;
            return 1;
        }
    }
    //Short press
    btn_pressed = 0;
    return 0;
}

//Choice function for choosing between any number of options 
int get_choice(int num_choice){

    int choice = 0;
    int response = 0;

    while(response == 0){
        //Get input
        response = get_input();

        //Confirm
        if(response == 1)
            break;

        choice = (choice + 1) % num_choice;
        //Also update screen to indicate that choice changed
    }
    return choice;
}

// ------------ AI GENERATED COME BACK (gemini) ------

// 1. Read the RISC-V internal cycle counter
unsigned int get_cycles() {
    unsigned int cycles;
    // 'rdcycle' is a standard RISC-V instruction that returns the 
    // number of clock cycles executed since the processor booted.
    asm volatile ("rdcycle %0" : "=r" (cycles));
    return cycles;
}

// 2. Linear Congruential Generator (from previous step)
static unsigned int next = 1;

void my_srand(unsigned int seed) {
    next = seed;
}

int my_rand(void) {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}