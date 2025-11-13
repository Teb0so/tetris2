#ifndef GAME_H
#define GAME_H

#include "assets.h"

typedef struct {
    Table table;
    Piece piece;
    int state;
} Game;

extern void game_init(Game *g);
extern void game_initpiece(Game *g);
extern void game_drawtable(Game *g);

#endif // GAME_H
