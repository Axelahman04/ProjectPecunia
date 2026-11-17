#include "graphics.h"

struct frame {
    char pixel_buffer[320*240];
};

void display_frame(struct frame_data *data) {
    volatile char *VGA = (volatile char*) 0x08000000;

    for (int i = 0; i < 320*480; i++)
        VGA[i] = data->background_color;
    
    int object_list_length = sizeof(data->object_list) / sizeof(Card);
    for (int i = 0; i < object_list_length; i++) {
        Card object = data->object_list[i];
        
        int position = object.pos_x + (object.pos_y * 320); 
        VGA[position] = 0xFF;
    }
}


void background() {

}