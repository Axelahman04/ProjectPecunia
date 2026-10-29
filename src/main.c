#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"

void start_ride_the_bus();
void start_blackjack();
typedef struct Deck;

int main(){
    srand(time(NULL));
    start_blackjack(); 

    return 0;
}