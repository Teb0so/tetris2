#include <curses.h>
#include <string.h>
#include "assets.h"
#include "game.h"

void game_init(Game *g) {
    table_init(&g->table);
    game_initpiece(g);
    g->running = true;
}

//TODO: implement random piece getter
void game_initpiece(Game *g) {
    g->piece.piece = 'o';
    g->piece.rotation = 0;
    g->piece.x = 4;
    g->piece.y = 10;
    set_piecearr(&g->piece, g->piece.piece);
    memset(g->piece.table, 0, sizeof(g->piece.table));
}

void game_movepiece(Game *g, int nx, int ny) {
    for(int i = g->piece.y; i <= g->piece.y + 3; i++) {
        for(int j = g->piece.x; j <= g->piece.x + 3; j++) {
            if(g->piece.table[i][j] == TILE && g->table.tiles[i + ny][j + nx] == TILE) {
                return;
            }
        }
    }

    g->piece.x = g->piece.x + nx;
    g->piece.y = g->piece.y + ny;
}

void game_inputhandler(Game *g) {
    int ch = getch();

    switch(ch){
        case 'q': g->running = false; break;
        case 'a': game_movepiece(g, - 1, 0); break;
        case 's': game_movepiece(g, 0, 1); break;
        case 'd': game_movepiece(g, 1, 0); break;
        case 'w': game_movepiece(g, 0, - 1); break;
    }
}

void game_drawtable(Game *g) {
    for(int i = OFFSET; i < ROWS - 1; i++) {
        for(int j = OFFSET; j < COLS - 1; j++) {
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

    memset(g->piece.table, 0, sizeof(g->piece.table));

    switch(g->piece.piece) {
        case 'i': piece_size = 3; break;
        default:  piece_size = 2; break;
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
