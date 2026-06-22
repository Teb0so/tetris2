#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "assets.h"
#include "window.h"

#define GAME_WIDTH 68
#define GAME_HEIGHT 20

typedef struct {
    unsigned int score;
    unsigned int level;
    unsigned int lines;

    unsigned int t;
    unsigned int j;
    unsigned int z;
    unsigned int o;
    unsigned int s;
    unsigned int l;
    unsigned int i;
} Score;

typedef struct {
    bool running;
    bool preview;
    bool harddrop;
    bool paused;
    int frame;
    Table table;
    Piece piece;
    Score score;
} Game;

extern void game_init(Game *g, int startlevel);
extern void game_topoutchecker(Game *g);
extern void game_initpiece(Game *g);
extern void game_fallpiece(Game *g);
extern void game_drawtable(Game *g, Window w);
extern void game_drawpiece(Game *g);
extern void game_drawstats(Game *g, Window w);
extern void game_drawstatsl(Game *g, Window w);
extern void game_levelchecker(Game *g);
extern void game_inputhandler(Game *g);
extern void game_clearline(Game *g, Window);

#endif // GAME_H
