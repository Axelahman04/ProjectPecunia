#include "deck.h"
#include "card_graphic.h"

volatile int *const VGA_CTRL = (volatile int *) 0x04000100; 
volatile char *const VGA_BUFFER_0 = (volatile char *) 0x08000000; 
volatile char *const VGA_BUFFER_1 = (volatile char *) 0x08000000 + 320*240;
volatile char *CURRENT_BUFFER = VGA_BUFFER_1;

struct frame_data {
    char background_color;
    
    Card *object_list;
    int object_pointer;
};

void swap_buffers() {

    *(VGA_CTRL + 1) = (unsigned int) CURRENT_BUFFER;

    *(VGA_CTRL + 0) = 0;

    while (*(VGA_CTRL + 3) & 1) {
        // wait
    }
    if (CURRENT_BUFFER == VGA_BUFFER_0) {
        CURRENT_BUFFER = VGA_BUFFER_1;
    } else {
        CURRENT_BUFFER = VGA_BUFFER_0;
    }
}


void draw_object(Card object, volatile char* frame){
    int start_pos = object.pos_x + (object.pos_y * 320); 

    char real_color;
    if (card_color(&object)) 
        real_color = 0x00;
    else 
        real_color = 0xC0;

    for (int x_offset = 0; x_offset < CARD_WIDTH; x_offset++) {
        for (int y_offset = 0; y_offset < CARD_HEIGHT; y_offset++) {
            char color = card_sprite[x_offset + (y_offset * CARD_WIDTH)];

            if (color == 0xE3)
                color = real_color;
            
            frame[start_pos + x_offset + (y_offset * 320)] = color;
        }
    }
}


void display_frame(struct frame_data *data) {
    volatile char *VGA = (volatile char*) CURRENT_BUFFER;

    for (int i = 0; i < 320*240; i++)
        VGA[i] = data->background_color;

    for (int i = 0; i < data->object_pointer; i++) {
        Card object = data->object_list[i];
        
        draw_object(object, VGA);
    }

    swap_buffers();
}