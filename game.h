#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

extern int current_y;
extern int current_x;

extern bool running;
extern int rotation;
extern char ch;
extern char current_piece;

extern void input_handler();
extern void rotation_handler(char piece, int new_rotation);
extern void falling_handler();
extern void draw_piece(char piece);
extern void draw_table();
extern void get_random_piece();
extern void colision_checker();
extern void add_piece();

#endif //GAME_H
