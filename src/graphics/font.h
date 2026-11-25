/*
Contains all letters and numbers for printing, symbols
*/

#ifndef FONT_H
#define FONT_H

#define FONT_W     8
#define FONT_H     8
#define FONT_FIRST 32   // ' '
#define FONT_LAST  90   // 'Z'

extern const unsigned char font8x8[FONT_LAST - FONT_FIRST + 1][FONT_H];

void draw_char(int x, int y, char c, unsigned char color, int scale);
void draw_string(int x, int y, const char *s, unsigned char color, int scale);

#endif