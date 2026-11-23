#include "deck.h"
#include "graphics.h"

volatile int *const VGA_CTRL = (volatile int *) 0x04000100; 
volatile char *const VGA_BUFFER_0 = (volatile char *) 0x08000000; 
volatile char *const VGA_BUFFER_1 = (volatile char *) 0x08000000 + 320*240;
volatile char *CURRENT_BUFFER = VGA_BUFFER_1;

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


void draw_object(Sprite object, volatile char* frame){

    int start_pos;
    switch (object.type){
        case SPRITE_CARD:
            start_pos = object.data.card_sprite.card.pos_x + object.data.card_sprite.card.pos_y * 320;
            break;
        case SPRITE_BUTTON:
            start_pos = object.data.button_sprite.button.pos_x + object.data.button_sprite.button.pos_y * 320;
            break;
        default:
            start_pos = 0;
            break;
    }

    for (int x_offset = 0; x_offset < object.width; x_offset++) {
        for (int y_offset = 0; y_offset < object.height; y_offset++) {
            char color = object.pixels[x_offset + (y_offset * object.width)];

            if (color == 0xE3)
                color = object.states[object.current_state];
            
            frame[start_pos + x_offset + (y_offset * 320)] = color;
        }
    }
}


void display_frame(struct frame_data *data) {
    volatile char *VGA = (volatile char*) CURRENT_BUFFER;

    for (int i = 0; i < 320*240; i++)
        VGA[i] = data->background_color;

    for (int i = 0; i < data->object_pointer; i++) {
        Sprite object = data->object_list[i];
        
        draw_object(object, VGA);
    }

    swap_buffers();
}