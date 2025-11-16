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
    g->piece.piece = 't';
    g->piece.rotation = 0;
    g->piece.x = 4;
    g->piece.y = 10;
    set_piecearr(&g->piece, g->piece.piece);
    memset(g->piece.table, 0, sizeof(g->piece.table));
}

// Checks if movement is valid
bool game_checkmovement(Game *g, int nx, int ny) {
    for(int i = g->piece.y; i <= g->piece.y + 3; i++) {
        for(int j = g->piece.x; j <= g->piece.x + 3; j++) {
            if(g->piece.table[i][j] == TILE && g->table.tiles[i + ny][j + nx] == TILE) {
                return false;
            }
        }
    }
    return true;
}

void game_movepiece(Game *g, int nx, int ny) {
    g->piece.x = g->piece.x + nx;
    g->piece.y = g->piece.y + ny;
}

// Checks if rotation is valid
bool game_rotatepiece(Game *g, int nr) {
    int piece_size;
    int array[4][4];
    int nrotation = g->piece.rotation + nr;

    switch(g->piece.piece) {
        case 'i': piece_size = 3; break;
        default:  piece_size = 2; break;
    };

    // Rotate piece
    for (int i = 0; i <= piece_size; i++) {
        for (int j = 0; j <= piece_size; j++) {
            switch(nrotation) {
                case 0: array[i][j] = g->piece.array[i][j]; break;
                case 1: array[j][piece_size - i] = g->piece.array[i][j]; break;
                case 2: array[piece_size - i][piece_size - j] = g->piece.array[i][j]; break;
                case 3: array[piece_size - i][j] = g->piece.array[j][i]; break;
            }
        }
    }

    // Check colision
    for(int i = 0; i <= piece_size; i++) {
        for(int j = 0; j <= piece_size; j++) {
            if(array[i][j] == TILE && g->table.tiles[i + g->piece.y][j + g->piece.x] == TILE) {
                return false;
            }
        }
    }
    return true;
}

void game_inputhandler(Game *g) {
    int ch = getch();

    switch(ch){
        case 'q': g->running = false; break;
        case 'j': if (game_rotatepiece(g, - 1)) { g->piece.rotation --;} break;
        case 'k': if (game_rotatepiece(g, 1)) { g->piece.rotation ++;} break;
        case 'w': if (game_checkmovement(g, 0, - 1)) { game_movepiece(g, 0, - 1);} break;
        case 'a': if (game_checkmovement(g, - 1, 0)) { game_movepiece(g, - 1, 0);} break;
        case 'd': if (game_checkmovement(g, 1, 0)) { game_movepiece(g, 1, 0);} break;
        case 's': if (game_checkmovement(g, 0, 1)) { game_movepiece(g, 0, 1);} break;
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
    int array[4][4];

    memset(g->piece.table, 0, sizeof(g->piece.table));

    switch(g->piece.piece) {
        case 'i': piece_size = 3; break;
        default:  piece_size = 2; break;
    };

    // Rotate piece
    for (int i = 0; i <= piece_size; i++) {
        for (int j = 0; j <= piece_size; j++) {
            switch(g->piece.rotation) {
                case 0: array[i][j] = g->piece.array[i][j]; break;
                case 1: array[j][piece_size - i] = g->piece.array[i][j]; break;
                case 2: array[piece_size - i][piece_size - j] = g->piece.array[i][j]; break;
                case 3: array[piece_size - i][j] = g->piece.array[j][i]; break;
            }
        }
    }

    // Draw piece to falling piece table
    for(int i = 0; i <= piece_size; i++) {
        for(int j = 0; j <= piece_size; j++) {
            if(array[i][j] == EMPTY) {
                g->piece.table[g->piece.y + i][g->piece.x + j] = EMPTY;
            }
            else {
                g->piece.table[g->piece.y + i][g->piece.x + j] = TILE;
            }
        }
    }
}
