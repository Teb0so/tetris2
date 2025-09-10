#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define TABLE_ROWS 20
#define TABLE_COLUMNS 10

extern int table[TABLE_ROWS][TABLE_COLUMNS];

extern int current_y;
extern int current_x;

extern bool running;
extern int rotation;
extern char ch;
extern char current_piece;

extern void input_handler();
extern void rotation_handler(char piece, int new_rotation);
void falling_handler();
extern void draw_piece(char piece);
extern void draw_table();
extern char get_random_piece();

#endif //GAME_H
