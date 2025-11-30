#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "assets.h"
#include "game.h"

void game_init(Game *g) {
    srand(clock());
    table_init(&g->table);
    game_initpiece(g);
    g->running = true;
    g->frame = 0;
    g->level = 0;
}

void game_score(Game *g, int score) {
    g->score = g->score + score;
}

char randompiece() {
    uint8_t npiece = rand() % PIECE_AMOUNT;
    char piece_char;

    switch(npiece) {
        case 0: piece_char = 'i'; break;
        case 1: piece_char = 'o'; break;
        case 2: piece_char = 'j'; break;
        case 3: piece_char = 'l'; break;
        case 4: piece_char = 's'; break;
        case 5: piece_char = 't'; break;
        case 6: piece_char = 'z'; break;
    }
    return piece_char;
}

void game_initpiece(Game *g) {
    // g->piece.piece = 'i';
    g->piece.piece = randompiece();
    g->piece.rotation = 0;
    if(g->piece.piece == 'i') {g->piece.y = 0;} else {g->piece.y = 1;}
    switch(g->piece.piece) {
        case 'i': case 'o': g->piece.x = OFFSET + 3; break;
        default:  g->piece.x = OFFSET + 4; break;
    }
    set_piecearr(&g->piece, g->piece.piece);
    memset(g->piece.table, EMPTY, sizeof(g->piece.table));
}

void game_topoutchecker(Game *g) {
    for(int i = OFFSET; i < COLS; i++) {
        if(g->table.tiles[OFFSET + 1][i] == TILE && g->piece.table[OFFSET + 1][i] == TILE) {
            g->running = false;
        }
    }
}

void game_shiftlines(Game *g, int line) {
    // Shift lines down
    for(int i = line; i > 0; i--) {
        for(int j = OFFSET; j < COLS - 1; j++) {
            g->table.tiles[i][j] = g->table.tiles[i - 1][j];
        }
    }
    for (int i = OFFSET; i < COLS - 1; i++) {
        g->table.tiles[0][i] = EMPTY;
    }
}

void game_clearline(Game* g) {
    int line;
    int cleared_lines = 0;
    for(int i = 0; i < ROWS - 1; i++) {
        for(int j = OFFSET; j < COLS - 1; j++) {
            if(g->table.tiles[i][j] == EMPTY) {
                break;
            }
            // Clear lines
            if(j == 11) {
                for(int k = OFFSET; k < COLS - 1; k++) {
                    erase();
                    g->table.tiles[i][k] = 0;
                    game_drawtable(g);
                    usleep(10000);
                    refresh();
                    line = i;
                }
                cleared_lines++;
                game_shiftlines(g, line);
                i = 0;
            }
        }
    }
    // Score
    switch (cleared_lines) {
        case (1): game_score(g, 40   * (g->level + 1)); break;
        case (2): game_score(g, 100  * (g->level + 1)); break;
        case (3): game_score(g, 300  * (g->level + 1)); break;
        case (4): game_score(g, 1200 * (g->level + 1)); break;
    }
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

void game_placepiece(Game *g){
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(g->piece.table[i][j] == TILE){
                g->table.tiles[i][j] = 1;
            }
        }
    }
    memset(g->piece.table, EMPTY, sizeof(g->piece.table));
    g->frame = 0;
    game_initpiece(g);
}

void game_fallpiece(Game *g){
    if(g->frame >= 48) {
        if(game_checkmovement(g, 0, 1)){
            game_movepiece(g, 0, 1);
            g->frame = 0;
        }
        else {
            game_placepiece(g);
        }
    }
}

// Set the right new rotation depending on the current piece
int game_checkrotation(Game *g, int nr) {
    int nrotation = g->piece.rotation + nr;
    int rotation = 0;

    switch(g->piece.piece) {
        case 'o':
            rotation = 0;
            break;
        case 'i': case 's': case 'z':
            if(nrotation < 0) {rotation = 3;}
            else if(nrotation == 0) {rotation = 0;}
            else if(nrotation == 1) {rotation = 3;}
            else if(nrotation == 2) {rotation = 0;}
            else if(nrotation == 3) {rotation = 3;}
            if(nrotation > 3) {rotation = 0;}
            break;
        case 'j': case 'l': case 't':
            if(nrotation < 0) {rotation = 3;}
            else if(nrotation >= 0 || nrotation <= 3) {rotation = nrotation;}
            if(nrotation > 3) {rotation = 0;}
            break;
    }
    return rotation;
}

// Checks if rotation is valid
bool game_rotatepiece(Game *g, int nr) {
    int piece_size;
    int array[4][4];

    switch(g->piece.piece) {
        case 'i': piece_size = 3; break;
        default:  piece_size = 2; break;
    };

    // Rotate piece
    for (int i = 0; i <= piece_size; i++) {
        for (int j = 0; j <= piece_size; j++) {
            switch(nr) {
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
        case 'j': if (game_rotatepiece(g, game_checkrotation(g, - 1))) {g->piece.rotation = game_checkrotation(g, - 1);} break;
        case 'k': if (game_rotatepiece(g, game_checkrotation(g, 1))) {g->piece.rotation = game_checkrotation(g, 1);} break;
        case 'w': if (game_checkmovement(g, 0, - 1)) { game_movepiece(g, 0, - 1);} break;
        case 'a': if (game_checkmovement(g, - 1, 0)) { game_movepiece(g, - 1, 0);} break;
        case 'd': if (game_checkmovement(g, 1, 0)) { game_movepiece(g, 1, 0);} break;
        case 's': if (game_checkmovement(g, 0, 1)) { game_movepiece(g, 0, 1);}
                  else {game_placepiece(g);} break;
    }
}

void game_drawscore(Game *g) {
    mvprintw(0, 30, "Score: %d", g->score);
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
