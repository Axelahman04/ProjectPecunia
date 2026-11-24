#include "../deck.h"

int clamp(int value, int min, int max);

static float balance = 1000.0;

struct ride_the_bus {
    Deck deck;

    Card cards[4];
    int drawn_cards;

    int bet_amount;
    int multiplier;
    int round;
    int choice;
};

static int place_bet() {  
    //printf("How much do you want to bet?\n");   
    
    //Get real bet amount
    int bet_amount = 100;

    return bet_amount;
}

static int is_inside(int value1, int value2, int value3) {
    int high;
    int low;
    
    if (value1 > value2){
        high = value1;
        low = value2;
    }

    if (value2 > value1){
        high = value2;
        low = value1;
    }   
    
    return low <= value3 && value3 <= high;
}

static int evaluate_round(struct ride_the_bus *game) {

    switch(game->round){
        case 1:
            //Logic for round 1
            if((game->choice)-1 == card_color(&game->cards[0])){
                game->multiplier = 2;
                return 0;
            }
            break;

        case 2:
            //Logic for round 2, 1 for next card lower, 2 for next card higher
            if(game->choice == 1 && game->cards[0].value > game->cards[1].value){
                game->multiplier = 3;
                return 0;
            }

            if(game->choice == 2 && game->cards[0].value < game->cards[1].value){
                game->multiplier = 3;
                return 0;
            }
            break;

        case 3:
        {
            //Logic for round 3
            int card1 = game->cards[0].value;
            int card2 = game->cards[1].value;
            int card3 = game->cards[2].value;

            int inside = is_inside(card1, card2, card3);

            if(game->choice == 1 && inside){
                game->multiplier = 4;
                return 0;
            }
            if(game->choice == 2 && !inside){
                game->multiplier = 4;
                return 0;
            }
        }
            break;

        case 4:
            //Logic for round 4
            if((game->choice)-1 == game->cards[3].suit){
                game->multiplier = 20;
                return 0;
            }
    }
    return 1;
}

static void get_input(struct ride_the_bus *game) {
    if (game->round < 4){
        //printf("0:Forfeit, 1, 2\n"); 
        //game->choice = get_number_input(0,2); 
    }
    
    if (game->round == 4){
        //printf("0:Forfeit, 1, 2, 3, 4\n"); 
        //game->choice = get_number_input(0,4); 
    }
    return;
}

static void draw_card(struct ride_the_bus *game) {
    Card new_card = next_card(&game->deck);

    game->cards[game->drawn_cards] = new_card;
    game->drawn_cards++;

}

static int start_round(struct ride_the_bus *game) {

    //Get input, player chooses
    get_input(game);

    //Check for forfeit
    if(game->choice == 0){
        balance += game->bet_amount * game-> multiplier;
        return 0;
    }

    //Draw card
    draw_card(game);

    //Evaluate_round, lost = return 1
    if(evaluate_round(game)){
        //printf("You lost!\n");
        return 1;
    }

    //Round won
    //printf("You win!\n"); 

    //Increment round
    if(game->round < 4){
        game->round++;
        return start_round(game);
    }
    //All rounds won
    balance += game->bet_amount * game-> multiplier;
    return 0;
}

static struct ride_the_bus init_game() {
    struct ride_the_bus game;

    Deck deck;
    deck_init(&deck, 1);
    shuffle_deck(&deck);

    game.deck = deck;
    game.drawn_cards = 0;

    game.bet_amount = place_bet();
    game.round = 1;
    game.multiplier = 1;

    return game;
}

void start_ride_the_bus() {
    while(balance > 0){
        //printf("Welcome to Ride The Bus!\n"); 
        //printf("Your balance: %d\n", (int) balance);
        
        struct ride_the_bus game = init_game();
        balance -= game.bet_amount;

        //display_frame(&game.frame);

        start_round(&game);
    }
}