#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "graphics.h"

void display_frame(struct frame_data *data);
void start_ride_the_bus();
void start_blackjack();
void my_srand(unsigned int seed);
unsigned int get_cycles();
typedef struct Deck;
extern void enable_interrupt();

volatile int *btn_pointer = (volatile int*)0x040000d0;

int btn1_pressed = 0;
int selected_game = 0; //0:Blackjack, 1:Ride The Bus, 2:Third game

int main(){

    int r_seed = get_cycles();
    my_srand(r_seed); 

    struct frame_data starting_frame;
    starting_frame.background_color = 0x1E;
    display_frame(&starting_frame);

    *(btn_pointer + 3) = 1;
    *(btn_pointer + 2) = 1;
    enable_interrupt();

    while(1){
        if(selected_game == 0){
            starting_frame.background_color = 0x2E;
            display_frame(&starting_frame);
        }
        if(selected_game == 1){
            starting_frame.background_color = 0x3E;
            display_frame(&starting_frame);
        }
        if(selected_game == 2){
            starting_frame.background_color = 0x4E;
            display_frame(&starting_frame);
        }
    }

    return 0;
}

void handle_interrupt(unsigned cause){

    switch(cause){
        //Button Interrupt
        case 18:
            *(btn_pointer + 3) = 1;
            btn1_pressed = 1;
            selected_game++;
    }
}