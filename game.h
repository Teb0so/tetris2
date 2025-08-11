#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

extern bool running;
extern int rotation;
extern char ch;
extern char current_piece;

extern void input_handler();
extern void rotation_handler(char piece, int new_rotation);
extern void draw_piece(char piece);

#endif //GAME_H
