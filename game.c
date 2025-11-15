#include <curses.h>
#include "assets.h"
#include "game.h"

void game_init(Game *g) {
    table_init(&g->table);
    game_initpiece(g);
    g->running = true;
}

void game_initpiece(Game *g) {
    //TODO: implement random piece getter
    set_piecearr(&g->piece);

    for(int i = 0; i <= ROWS; i++){
        for(int j = 0; j <= ROWS; j++){
            g->piece.table[i][j] = 0;
        }
    }

    g->piece.piece = 't';
    g->piece.rotation = 0;
    g->piece.x = 4;
    g->piece.y = 2;
}

void game_inputhandler(Game *g) {
    int ch = getch();

    switch(ch){
        case 'q': g->running = false; break;
    }
}

void game_drawtable(Game *g) {
    for(int i = 1; i < ROWS - 1; i++) {
        for(int j = 1; j < COLS - 1; j++) {
            if(g->table.tiles[i][j] == EMPTY && g->piece.table[i][j] == EMPTY) {
                printw(EMPTY_TILE);
            }
            else if(g->table.tiles[i][j] == TILE || g->piece.table[i][j] == TILE) {
                printw(FILLED_TILE);
            }
        }
        printw("\n");
    }
}

void game_drawpiece(Game *g) {
    int piece_size;

    switch(g->piece.piece) {
        case 'o': case 'i': piece_size = 3; break;
        default:            piece_size = 2; break;
    };

    for(int i = 0; i <= piece_size; i++) {
        for(int j = 0; j <= piece_size; j++) {
            if(g->piece.array[i][j] == EMPTY) {
                g->piece.table[g->piece.y + i][g->piece.x + j] = EMPTY;
            }
            else {
                g->piece.table[g->piece.y + i][g->piece.x + j] = TILE;
            }
        }
    }
}
