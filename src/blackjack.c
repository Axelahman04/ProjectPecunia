#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

int get_number_input(int min, int max);
int clamp(int value, int min, int max);

static float balance = 1000.0;

struct blackjack {
    Deck deck;
    Card player_hand[11];
    int player_pointer;

    Card dealer_hand[11];
    int dealer_pointer;
    int bet_amount;
};

void draw_card_player(struct blackjack *game) {
    Card new_card = next_card(&game->deck);
    printf("Drew a card for player:\n");
    display_card(&new_card);

    game->player_hand[game->player_pointer] = new_card;
    game->player_pointer++;
}

void draw_card_dealer(struct blackjack *game, int hidden) {
    Card new_card = next_card(&game->deck);
    if (hidden == 0) {
        printf("Drew a card for dealer:\n");
        display_card(&new_card);
    }

    game->dealer_hand[game->dealer_pointer] = new_card;
    game->dealer_pointer++;
}

int hand_value(Card *hand, int hand_pointer, int *ace_count) {
    int value = 0;
    *ace_count = 0;

    for (int i=0; i < hand_pointer; i++) {
        int card_value = hand[i].value;

        if (card_value == 14) {
            card_value = 11;
            *ace_count++;
        } else {
            card_value = clamp(card_value, 0, 10);
        }

        value += card_value;
    }

    while (value > 21 && *ace_count > 0) {
        value -= 10;
        *ace_count--;
    }

    return value;
}


int place_bet() {  
    printf("How much do you want to bet?\n");   
    int bet_amount = get_number_input(1,(int) balance);  

    printf("You successfully bet: %d dollars!\n", bet_amount);
    return bet_amount;
}

int player_turn(struct blackjack *game) {
    int ace_count = 0;
    int hand_v = hand_value(game->player_hand, game->player_pointer, &ace_count); 
    printf("Your current hand is totals to  %d, and you have %d Aces. Do you want to Stand (0) or Hit (1)\n?", hand_v, ace_count);
    
    int response = get_number_input(0, 1);
    if (response == 0)
        return 0;
    
    draw_card_player(game);
    int new_hand_v = hand_value(game->player_hand, game->player_pointer, &ace_count);

    if (new_hand_v > 21) {
        printf("Your new hand totals to %d, and you have %d aces\n", new_hand_v, ace_count);
        return 1;
    }
    
    player_turn(game);
}

void dealer_turn(struct blackjack *game, int reveal) {
    int ace_count = 0;
    if (reveal == 1) {
        int hand_v = hand_value(game->dealer_hand, game->dealer_pointer, &ace_count); 
    
        printf("The dealer reveals his card:\n");
        display_card(&game->dealer_hand[1]);
        printf("His hand is %d\n", hand_v);
        
        if (hand_v >= 17) {
            return;
        }
    }
    
    draw_card_dealer(game, 0);
    int new_hand_v = hand_value(game->dealer_hand, game->dealer_pointer, &ace_count);
    printf("Dealers new hand totals to %d\n", new_hand_v);

    if (new_hand_v > 17) {
        return;
    }
    
    dealer_turn(game, 0);
}

int start_sequence(struct blackjack *game){
    draw_card_player(game);
    draw_card_dealer(game, 0);
    draw_card_player(game);
    draw_card_dealer(game, 1);

    int ace_count = 0;
    int dealer_hand_v = hand_value(game->dealer_hand, game->dealer_pointer, &ace_count);
    
    if (dealer_hand_v == 21) 
        return 1;
    return 0;
}

void evaluate_win(struct blackjack *game){
    int ace_count = 0;
    int player_hand_value = hand_value(game->player_hand, game->player_pointer, &ace_count);
    int dealer_hand_value = hand_value(game->dealer_hand, game->dealer_pointer, &ace_count);

    int player_hand_size = sizeof(game->player_hand) / sizeof(Card);

    if (player_hand_value < dealer_hand_value && dealer_hand_value > 21) {
        printf("Dealer won :(\n");
    } else if (player_hand_value == dealer_hand_value) {
        printf("Same value, push :/\n");
        balance += game->bet_amount;
    } else if (player_hand_value == 21 && (deck_contains(game->player_hand, 14) && player_hand_size == 2)) {
        printf("You got a blackjack! You get 2.5x bet amount!\n");
        balance += (float) game->bet_amount * 2.5;
    } else {
        printf("You won! You get 2x bet amount!\n");
        balance += game->bet_amount * 2;
    }
}

struct blackjack init_game(){
    struct blackjack game;

    Deck deck;
    deck_init(&deck, 8);
    shuffle_deck(&deck);     
    
    game.deck = deck;
    game.player_pointer = 0;
    game.dealer_pointer = 0;

    game.bet_amount = place_bet();

    return game;
}

void start_blackjack() {
    printf("Welcome to Blackjack!\n"); 
    printf("Your balance: %f\n", (int) balance); 

    struct blackjack game = init_game();
    balance -= game.bet_amount;

    int response = start_sequence(&game);
    if (response == 1) {
        printf("The dealer reveals his card:\n");
        display_card(&game.dealer_hand[1]);

        printf("Dealer has 21, you lose :(\n");
        return;
    }

    response = player_turn(&game);

    if (response == 1){
        printf("Your hand is over 21, that's a bust :(\n");
        return;
    }

    dealer_turn(&game, 1);
    evaluate_win(&game);
}

