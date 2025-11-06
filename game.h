#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "assets.h"

typedef struct {
    char piece;
    int rotation;
    int y;
    int x;
} CurrentPiece;

typedef struct {
    CurrentPiece current_piece;
    Table table;
    int frame;
    bool running;
} Game;

extern void game_init(Game *g);
extern bool game_get_state(Game *g);
extern void dbg_info(Game *g);
extern void game_increase_frame(Game *g);
extern void input_handler(Game *g);
extern void rotation_handler(Game *g, int new_rotation);
extern void falling_handler(Game *g);
extern void draw_piece(Game *g);
extern void draw_table(Game *g);
extern void get_random_piece(Game *g);
extern void colision_checker(Game *g);
extern void add_piece(Game *g);

#endif //GAME_H
