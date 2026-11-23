#include "card_graphic.h"

typedef enum {
    SPRITE_CARD
} SpriteType;

typedef struct {
    Card card;
} CardSprite;

typedef struct {
    SpriteType type;

    int current_state;
    const unsigned char *states;

    int width;
    int height;
    const unsigned char *pixels;

    union {
        CardSprite card_sprite;
    } data;
} Sprite;

Sprite create_card_sprite(Card c, int state) {
    Sprite s;
    s.data.card_sprite.card = c;
    s.type = SPRITE_CARD;
    s.states = CARD_STATES;
    s.pixels = card_sprite;
    s.current_state = state;
    return s;
}

struct frame_data {
    char background_color;

    Sprite *object_list;
    int object_pointer;
};