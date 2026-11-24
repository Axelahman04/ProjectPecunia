#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "deck.h"
#include "action.h"

typedef enum {
    SPRITE_CARD,
    SPRITE_BUTTON
} SpriteType;

typedef struct {
    Button button;
} ButtonSprite;

typedef struct {
    Card card;
} CardSprite;

typedef struct {
    SpriteType type;
    int current_state;
    int max_state;
    const unsigned char *states;
    int width;
    int height;
    const unsigned char *pixels;
    union {
        CardSprite card_sprite;
        ButtonSprite button_sprite;
    } data;
} Sprite;

struct frame_data {
    char background_color;
    Sprite *object_list;
    int object_pointer;
};

// Bara deklarationer (prototyper) här!
void set_state_values(Sprite* s, int current_state, int max_state);
Sprite create_card_sprite(Card card, int state, int max_state);
Sprite create_button_sprite(Button button, int state, int max_state);

#endif