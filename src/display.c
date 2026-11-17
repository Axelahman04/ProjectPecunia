#include "graphics.h"

struct frame {
    char pixel_buffer[320*240];
};

void display_frame(struct frame_data *data) {
    volatile char *VGA = (volatile char*) 0x08000000;

    for (int i = 0; i < 320*480; i++)
        VGA[i] = data->background_color;

    for (int i = 0; i < data->object_pointer; i++) {
        Card object = data->object_list[i];
        
        int position = object.pos_x + (object.pos_y * 320); 
        VGA[position] = 0xFF;
    }
}


void background() {

}