#include <curses.h>
#include "assets.h"
#include "game.h"

void game_init(Game *g)
{
    table_init(&g->table);
}

void game_initpiece(Game *g)
{
    //TODO: implement random piece getter
    set_piecearr(&g->piece, 'i');
    g->piece.piece = 'i';
}

void game_drawtable(Game *g)
{
    for(int i = 1; i < ROWS - 1; i++) {
        for(int j = 1; j < COLS - 1; j++) {
            if(g->table.tiles[i][j] == EMPTY) {
                printw(EMPTY_TILE);
            }
            else {
                printw(FILLED_TILE);
            }
        }
        printw("\n");
    }
}
