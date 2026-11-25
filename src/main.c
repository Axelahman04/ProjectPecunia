#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"

void start_ride_the_bus();
void start_blackjack();
void my_srand(unsigned int seed);
int get_choice(int num_choice);
int enable_input();

unsigned int get_cycles();
typedef struct Deck;

extern void enable_interrupt();
void draw_background(char color);

int main(){

    int r_seed = get_cycles();
    my_srand(r_seed); 

    enable_interrupt();
    enable_input();

    while(1) {
        int game_picked = get_choice(2);

        switch(game_picked){
            case 0:
                //start_ride_the_bus();
                test_draw(0x1C);
                break;
            case 1:
                //start_ride_the_bus();
                test_draw(0x4E);
                break;
        }
    }
    return 0;
}