/*
Purpose:
Draws each frame

Functions:
    draw_react()
    draw_blackjack(game)
    draw_ride_the_bus(game)
    draw_menu()
*/

#define FRAME_WIDTH 320
#define FRAME_HEIGHT 240
#define POKER_COLOR 0x2D

extern volatile char* CURRENT_BUFFER;

void swap_buffer();
void draw_char(int x, int y, char c, unsigned char color, int scale);

void draw_blank_background(char color){
    for (int i = 0; i < (FRAME_WIDTH * FRAME_HEIGHT); i++)
        CURRENT_BUFFER[i] = color;
}

void draw_react(int x, int y, char color, int scale) {
    if (x < 0 || y < 0) {
        return;
    }

    int position = x + (y * FRAME_WIDTH);

    for (int i = 0; i < scale; i++) {
        for (int r = 0; r < scale; r++) {
            if ((position % 320)  + i > (FRAME_WIDTH - 1) || (position / 320) + r > (FRAME_HEIGHT -1)) {
                continue;
            }

            CURRENT_BUFFER[position + i + (r * FRAME_WIDTH)] = color;
        }
    }
}

void test_draw(int color) {
    draw_blank_background(POKER_COLOR);
    draw_char(100, 100, 'B', color, 1);

    swap_buffer();
}