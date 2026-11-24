#include "graphics.h"
#include "card_graphic.h"
#include "button_graphic.h"

void set_state_values(Sprite* s, int current_state, int max_state) {
    int state_space = sizeof(s->states) / sizeof(unsigned char); 

    if (max_state > state_space || max_state < 0) {
        max_state = state_space;
    } 

    if (current_state > max_state) {
        current_state = max_state;
    } 
}

Sprite create_card_sprite(Card card, int state, int max_state) {
    Sprite s;
    s.data.card_sprite.card = card;

    s.type = SPRITE_CARD;

    s.states = CARD_STATES;
    set_state_values(&s, state, max_state);

    s.pixels = card_sprite;
    s.width = CARD_WIDTH;
    s.height = CARD_HEIGHT;
    return s;
}


Sprite create_button_sprite(Button button, int state, int max_state) {
    Sprite s;
    s.data.button_sprite.button = button;

    s.type = SPRITE_BUTTON;

    s.states = BUTTON_STATES;
    set_state_values(&s, state, max_state);

    s.pixels = button_sprite;
    s.width = BUTTON_WIDTH;
    s.height = BUTTON_HEIGHT;
    return s;
}