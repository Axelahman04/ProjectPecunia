#include <stdio.h>
#include <stdlib.h>

int balance = 1000;
int bet_amount = 10;

//User input
int user_bet_amount_input;
int user_suit_choice_input;

void start_ride_the_bus(){
    printf("Welcome to Ride The Bus!\n"); 
    while(1){
        printf("Your balance: %d\n", balance); 

        printf("Please enter bet amount: \n"); 

        //Take user bet amount
        while(1){
            scanf("%d", &user_bet_amount_input);
            if(user_bet_amount_input >= 1 && user_bet_amount_input <= balance){
                bet_amount = user_bet_amount_input;
                break;
            } else {
                printf("Bet amount needs to be atleast 1 and at most %d\nPlease enter bet amount: \n", balance);
            }
        }

        printf("You successfully bet: %d dollars!\n", user_bet_amount_input);
        printf("Red (0) or Black (1)?\n");

        //Take user bet on color
        scanf("%d", &user_suit_choice_input);

        switch(user_suit_choice_input){
            case 0:
                printf("You successfully chose Red\n");
                break;
            case 1:
                printf("You sucessfully chose Black\n");
                break;
        }

        //Game picks a color (Red:0, Black:1)
        int random_first_suit = rand() % 2;

        //Print color of the drawn card
        switch(random_first_suit){
            case 0:
                printf("The card was red\n");
            case 1:
                printf("The card was black\n");
            }

        //Check if user won or lost
        if(user_suit_choice_input == random_first_suit){
            //WIN
            printf("You win, your bet has increased 2x to: %d dollars!\n", bet_amount * 2);
            break;
            } else{
                //LOSE
                balance -= bet_amount;
                printf("You lost. New balace: %d\n",balance);
            }
        }
    
    printf("This is round 2\n");
    
}
