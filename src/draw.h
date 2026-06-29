#ifndef DRAW_H
#define DRAW_H

#include "game.h"

extern int draw_getinput();
extern void draw_begin(Window *w);
extern void draw_end();
extern void draw(Game g, Window w);
extern void draw_table(Game g, Window w);
extern void draw_stats(Game g, Window w);
extern void draw_statsl(Game g, Window w);

#endif //DRAW_H
