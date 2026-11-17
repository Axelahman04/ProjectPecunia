#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "deck.h";

struct frame_data {
    char background_color;
    
    Card *object_list;
    int object_pointer;
};

#endif