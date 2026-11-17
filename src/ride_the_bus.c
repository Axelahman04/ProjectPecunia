#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

int get_number_input(int min, int max);


struct ride_the_bus {
    Deck deck;
    Card cards[4];
    int bet_amount;
};


int balance = 1000;


int ride_the_bus_money() {  
    int bet_amount = get_number_input(1,balance);  

    return bet_amount;
}

int stage_1(struct ride_the_bus* game) {
    int color = get_number_input(0,1);

    switch(color){
        case 0:
            break;
        case 1:
            break;
    }

    //Game picks a random card
    Card first_card = next_card(&game->deck);
    game->cards[0] = first_card;

    display_card(&first_card);         

    //Check if user won or lost
    if(color == card_color(&first_card)){
        //WIN
        return 1;
    } else{
        //LOSE
        return 0;
    }
} 

int stage_2(struct ride_the_bus* game){

    Card second_card = next_card(&game->deck);
    game->cards[1] = second_card;

    int choice = get_number_input(0,2); 

    display_card(&second_card); 

    //Forfeit
    if (choice == 2){
        return 2;
    }

    display_card(&second_card);

    if(game->cards[1].value < game->cards[0].value && choice == 0) {
        return 1;
    } else if (game->cards[1].value > game->cards[0].value && choice == 1) {
        return 1;
    }
    return 0;
}

int stage_4(struct ride_the_bus* game) {
    int choice = get_number_input(0,4); 

    if (choice == 4) {
        return 2;
    }
    
    //Game picks a random card
    Card fourth_card = next_card(&game->deck);
    game->cards[0] = fourth_card;

    display_card(&fourth_card);         

    //Check if user won or lost
    if(choice == &fourth_card.suit){
        //WIN
        return 1;
    } else{
        //LOSE
        return 0;
    }
}
int stage_3(struct ride_the_bus* game){

    Card third_card = next_card(&game->deck);
    game->cards[2] = third_card;

    int choice = get_number_input(0,2); 

    display_card(&third_card);   

    //Forfeit
    if (choice == 2){
        return 2;
    }

    //Check if third card is inside first two.
    if(game->cards[0].value <= game->cards[2].value){
        if(game->cards[2].value <= game->cards[1].value){
            if(choice == 0){
                return 1;
            }
        }
    }

    //Check if third card is outside first two. (lower)
    if(game->cards[0].value >= game->cards[2].value){
        if(game->cards[2].value <= game->cards[1].value){
            if(choice == 1){
                return 1;
            }
        }
    }

     //Check if third card is outside first two. (higher)
    if(game->cards[0].value <= game->cards[2].value){
        if(game->cards[2].value >= game->cards[1].value){
            if(choice == 1){
                return 1;
            }
        }
    }
    return 0;
}

void start_ride_the_bus(){

    while(1){
        struct ride_the_bus game;

        Deck deck;
        deck_init(&deck, 1);
        shuffle_deck(&deck);  

        game.deck = deck;
        
        game.bet_amount = ride_the_bus_money();

        int result = stage_1(&game);

        if (result == 1) {
        } else {
            balance -= game.bet_amount;
            continue;
        }

        result = stage_2(&game);

        switch (result) {
            case 0:
                balance -= game.bet_amount;
                continue;
            case 1:
                break;
            case 2:
                balance += game.bet_amount;
                continue;

        }

        result = stage_3(&game);

        switch (result) {
            case 0:
                balance -= game.bet_amount;
                continue;
            case 1:
                break;
            case 2:
                balance += game.bet_amount * 2;
                continue;
        }

        result = stage_4(&game);

        switch (result) {
            case 0:
                balance -= game.bet_amount;
                continue;
            case 1:
                balance += game.bet_amount * 19;
                break;
            case 2:
                balance += game.bet_amount * 3;
                continue;
        }

    }
}
