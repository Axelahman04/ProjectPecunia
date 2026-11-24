#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "graphics.h"

void display_frame(struct frame_data *data);
void start_ride_the_bus();
void start_blackjack();
void my_srand(unsigned int seed);
int get_choice(int num_choice);
int enable_input();

unsigned int get_cycles();
typedef struct Deck;

extern void enable_interrupt();
extern volatile int *btn_pointer;
extern volatile int btn_pressed;

int main(){

    int r_seed = get_cycles();
    my_srand(r_seed); 

    struct frame_data starting_frame;
    starting_frame.background_color = 0x1E;
    display_frame(&starting_frame);

    enable_interrupt();
    enable_input();

    int game_picked = get_choice(2);

    switch(game_picked){
        case 0:
            //start_blackjack;
            starting_frame.background_color = 0x2E;
            display_frame(&starting_frame);
            break;
        case 1:
            //start_ride_the_bus;
            starting_frame.background_color = 0x4E;
            display_frame(&starting_frame);
            break;
    }
    return 0;
}

void handle_interrupt(unsigned cause){

    switch(cause){
        //Button Interrupt
        case 18:
            *(btn_pointer + 3) = 1;
            btn_pressed = 1;
    }
}