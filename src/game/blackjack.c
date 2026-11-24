#include "../deck.h"

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

    new_card.pos_x = 80 + (40 * game->player_pointer);
    new_card.pos_y = 40 + (5 * game->player_pointer);
    int color = card_color(&new_card);

    game->player_hand[game->player_pointer] = new_card;
    game->player_pointer++;
}

void draw_card_dealer(struct blackjack *game, int hidden) {
    Card new_card = next_card(&game->deck);
    if (hidden == 0) {
        //Display
    }

    int color = card_color(&new_card); 

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
    //Get bet amount
    int bet_amount = 100;  

    return bet_amount;
}

int player_turn(struct blackjack *game) {
    int ace_count = 0;
    int hand_v = hand_value(game->player_hand, game->player_pointer, &ace_count); 
    
    //get real response
    int response = 0;
    if (response == 0)
        return 0;

    int new_hand_v = hand_value(game->player_hand, game->player_pointer, &ace_count);

    if (new_hand_v > 21) {
        return 1;
    }
    
    player_turn(game);
}

void dealer_turn(struct blackjack *game, int reveal) {
    int ace_count = 0;
    if (reveal == 1) {
        int hand_v = hand_value(game->dealer_hand, game->dealer_pointer, &ace_count); 
        
        if (hand_v >= 17) {
            return;
        }
    }
    
    draw_card_dealer(game, 0);

    int new_hand_v = hand_value(game->dealer_hand, game->dealer_pointer, &ace_count);

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

    } else if (player_hand_value == dealer_hand_value) {
        balance += game->bet_amount;
    } else if (player_hand_value == 21 && (deck_contains(game->player_hand, 14) && player_hand_size == 2)) {
        balance += (float) game->bet_amount * 2.5;
    } else {
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
    struct blackjack game = init_game();
    balance -= game.bet_amount;

    int response = start_sequence(&game);
}

