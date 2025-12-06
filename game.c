#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "assets.h"
#include "game.h"

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

void game_init(Game *g, int startlevel) {
    srand(clock());
    table_init(&g->table);
    g->piece.next = randompiece();
    game_initpiece(g);
    g->running = true;
    g->preview = true;
    g->harddrop = false;
    g->paused = false;
    g->frame = 0;
    g->score.level = startlevel;
    g->score.lines = 0;
}

void game_score(Game *g, int score) {
    g->score.score = g->score.score + score;
}

void game_initpiece(Game *g) {
    // g->piece.piece = 'i';
    g->piece.piece = g->piece.next;
    g->piece.next = randompiece();
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
        case (1): game_score(g, 40   * (g->score.level + 1)); break;
        case (2): game_score(g, 100  * (g->score.level + 1)); break;
        case (3): game_score(g, 300  * (g->score.level + 1)); break;
        case (4): game_score(g, 1200 * (g->score.level + 1)); break;
    }
    g->score.lines = g->score.lines + cleared_lines;
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
    game_score(g, g->score.level + 1);
    g->harddrop = false;
    memset(g->piece.table, EMPTY, sizeof(g->piece.table));
    g->frame = 0;
    game_initpiece(g);
}

void game_levelchecker(Game *g) {
    if((unsigned int) g->score.lines / 10 > g->score.level) {
        g->score.level = (unsigned int) g->score.lines / 10;
    }
}

void game_fallpiece(Game *g) {
    int gravity;

    if (g->harddrop) {
        gravity = 1;
        g->score.score++;
    }
    else {
        switch(g->score.level) {
            case 0: gravity = 48; break;
            case 1: gravity = 43; break;
            case 2: gravity = 38; break;
            case 3: gravity = 33; break;
            case 4: gravity = 28; break;
            case 5: gravity = 23; break;
            case 6: gravity = 18; break;
            case 7: gravity = 13; break;
            case 8: gravity = 8; break;
            case 9: gravity = 6; break;
            case 10:
            case 11:
            case 12: gravity = 5; break;
            case 13:
            case 14:
            case 15: gravity = 4; break;
            case 16:
            case 17:
            case 18: gravity = 3; break;
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
            case 26:
            case 27:
            case 28: gravity = 2; break;
            default: gravity = 1; break;
        }
    }

    if(g->frame >= gravity) {
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

void game_softdrop(Game *g) {
    if (game_checkmovement(g, 0, 1)) {
        game_movepiece(g, 0, 1);
    }
    // Prevent the falling piece entering a placed piece on soft drop
    else if (!game_checkmovement(g, 0, 0)) {
        game_movepiece(g, 0, - 1);
    }
    else {
        game_placepiece(g);
    }
}

void game_inputhandler(Game *g) {
    int ch = getch();

    switch(ch){
        case 'q': g->running = false; break;
        case 'n': if (g->preview) {g->preview = false;} else {g->preview = true;} break;
        case 'j': if (game_rotatepiece(g, game_checkrotation(g, - 1))) {g->piece.rotation = game_checkrotation(g, - 1);} break;
        case 'k': if (game_rotatepiece(g, game_checkrotation(g, 1))) {g->piece.rotation = game_checkrotation(g, 1);} break;
        // case 'w': if (game_checkmovement(g, 0, - 1)) { game_movepiece(g, 0, - 1);} break;
        case 'a': if (game_checkmovement(g, - 1, 0)) { game_movepiece(g, - 1, 0);} break;
        case 'd': if (game_checkmovement(g, 1, 0)) { game_movepiece(g, 1, 0);} break;
        case 's': game_softdrop(g); break;
        case ' ': g->harddrop = true; break;
        case 'p': if (g->paused == false) {g->paused = true;} else {g->paused = false;} break;
    }
}

void game_drawstats(Game *g) {
    mvprintw(0, 24, "Next:");

    if (g->preview) {
        switch(g->piece.next) {
            case 'i':
                mvprintw(2, 24, L1_PREVIEW_I);
                mvprintw(3, 24, L2_PREVIEW_I);
                break;
            case 'o':
                mvprintw(2, 24, L1_PREVIEW_O);
                mvprintw(3, 24, L2_PREVIEW_O);
                break;
            case 't':
                mvprintw(2, 24, L1_PREVIEW_T);
                mvprintw(3, 24, L2_PREVIEW_T);
                break;
            case 'j':
                mvprintw(2, 24, L1_PREVIEW_J);
                mvprintw(3, 24, L2_PREVIEW_J);
                break;
            case 'l':
                mvprintw(2, 24, L1_PREVIEW_L);
                mvprintw(3, 24, L2_PREVIEW_L);
                break;
            case 's':
                mvprintw(2, 24, L1_PREVIEW_S);
                mvprintw(3, 24, L2_PREVIEW_S);
                break;
            case 'z':
                mvprintw(2, 24, L1_PREVIEW_Z);
                mvprintw(3, 24, L2_PREVIEW_Z);
                break;
        }
    }

    mvprintw(5, 24, "Level: %d", g->score.level);
    mvprintw(6, 24, "Lines: %d", g->score.lines);
    mvprintw(7, 24, "Score: %d", g->score.score);
    if (g->paused) {mvprintw(9, 24, "PAUSED");}
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
