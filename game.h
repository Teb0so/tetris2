#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "assets.h"

typedef struct {
    Table table;
    Piece piece;
    int frame;
    bool running;
} Game;

extern void game_init(Game *g);
extern void game_initpiece(Game *g);
extern void game_fallpiece(Game *g);
extern void game_drawtable(Game *g);
extern void game_drawpiece(Game *g);
extern void game_inputhandler(Game *g);
extern void game_clearline(Game *g);

#endif // GAME_H
