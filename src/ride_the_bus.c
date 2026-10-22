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

void start_ride_the_bus(){
    printf("Welcome to Ride The Bus!\n"); 
    printf("Your balance: %d\n", balance); 

    while(1){
        struct ride_the_bus game;

        Deck deck;
        deck_init(&deck, 1);
        shuffle_deck(&deck);  

        game.deck = deck;
        
        game.bet_amount = ride_the_bus_money();

        int result = stage_1(&game);

        if (result == 1) {
            printf("You win, your bet has increased 2x to: %d dollars!\n", game.bet_amount * 2);
        } else {
            balance -= game.bet_amount;
            printf("You lost :(\n");
            continue;
        }

        result = stage_2(&game);

        switch (result) {
            case 0:
                balance -= game.bet_amount;
                printf("You lost :(\n");
                continue;
            case 1:
                printf("You win, your bet has increased 3x to: %d dollars!\n", game.bet_amount * 3);
                break;
            case 2:
                balance += game.bet_amount * 2;
                continue;

        }

        result = stage_4(&game);

        switch (result) {
            case 0:
                balance -= game.bet_amount;
                printf("You lost :(\n");
                continue;
            case 1:
                printf("You win, your bet has increased 20x to: %d dollars!\n", game.bet_amount * 20);
                balance += game.bet_amount * 20;
                break;
            case 2:
                balance += game.bet_amount * 4;
                continue;

        }

    }
    
    printf("This is round 2\n");
    
}


int ride_the_bus_money() {
    printf("Your balance is : %d\n", balance);   
    printf("How much do you want to bet?\n");   
    int bet_amount = get_number_input(1,balance);  

    printf("You successfully bet: %d dollars!\n", bet_amount);
    return bet_amount;
}

int stage_1(struct ride_the_bus* game) {
    printf("Red (0) or Black (1)?\n");

    int color = get_number_input(0,1);

    switch(color){
        case 0:
            printf("You successfully chose Red\n");
            break;
        case 1:
            printf("You sucessfully chose Black\n");
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

    printf("Will the next card be: Lower (0) or Higher (1), or do you want Forfeit (2) to keep your winnings?\n");
    int choice = get_number_input(0,2); 

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
    printf("What suit will the the next card be: Club (0), Diamond (1), Heart (2), Spade (3), or do you want to forfeit (4) and keep your winnings\n?");

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
