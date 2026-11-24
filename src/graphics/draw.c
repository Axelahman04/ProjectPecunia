extern volatile char *CURRENT_BUFFER;

void swap_buffer();

void draw_background(char color){
    for (int i = 0; i < 320*240; i++)
        CURRENT_BUFFER[i] = color;

    swap_buffer();
}