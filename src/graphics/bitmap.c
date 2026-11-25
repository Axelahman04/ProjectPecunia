void draw_react(int x, int y, char color, int scale);

void memcp(unsigned char* array_a, unsigned char* array_b, int size) {
<<<<<<< HEAD
    for (int i = 0; i < 2; i++) {
=======
    for (int i = 0; i < size; i++) {
>>>>>>> e6ea0da (Fix order and size of memcopy)
        array_a[i] = array_b[i];
    }
}

void draw_bitmap_1bit(const unsigned char *data, int w, int h,
    int x, int y, unsigned char color, int scale) {
        int start_x = x;
        int row_size = (w + 8 - 1) / 8;

        for (int r = 0; r < h; r++) {
            unsigned char* row;
            memcp(row, &data[r * row_size], row_size * sizeof(char));

            for (int c = 0; c < w; c++) {
                unsigned char bit = (row[c / 8] >> c) & 0x1;
                
                if (bit) {
                    draw_react(x, y, color, scale);
                } 
                x += scale;
            }
            x = start_x;
            y += scale;
        }
    }