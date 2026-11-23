#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"

void start_ride_the_bus();
void start_blackjack();
void my_srand(unsigned int seed);
unsigned int get_cycles();
typedef struct Deck;

int main(){
    int r_seed = get_cycles();
    my_srand(r_seed); 
    start_blackjack(); 

    return 0;
}

void handle_interrupt(unsigned cause){
// Here interupts can be handled
}