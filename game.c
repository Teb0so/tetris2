#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "./game.h"
#include "./assets.h"

void game_init(Game *g) {
    g->current_piece.x = 4;
    g->current_piece.y = 0;
    g->current_piece.rotation = 1;
    g->running = true;
}

bool game_get_state(Game*g) {
    return g->running;
}

void game_increase_frame(Game *g) {
    g->frame++;
}

void dbg_info(Game *g){
    printw("frame: %d\n", g->frame);
    printw("I: %d\n", i_piece.count);
    printw("O: %d\n", o_piece.count);
    printw("T: %d\n", t_piece.count);
    printw("J: %d\n", j_piece.count);
    printw("L: %d\n", l_piece.count);
    printw("S: %d\n", s_piece.count);
    printw("Z: %d\n", z_piece.count);
}

void add_piece() {
    for (int i = 0; i <= TABLE_ROWS; i++) {
        for (int j = 0; j <= TABLE_COLUMNS; j++) {
            if (table[i][j] == 1) {
                table[i][j] = 2;
            }
        }
    }
}

void colision_checker(Game *g) {
    for (int i = 0; i <= TABLE_ROWS; i++) {
        for (int j = 0; j <= TABLE_COLUMNS; j++) {
            if (table[i][j] == 1) {
                if (table[i + 1][j] != 1 && table[i + 1][j] != 0) {
                    add_piece();
                    get_random_piece(g);
                    g->current_piece.rotation = 1;
                    g->current_piece.y = 0;
                    g->current_piece.x = 4;
                }
            }
        }
    }
}

void falling_handler(Game *g) {
    if(g->frame == 23) {
        g->current_piece.y = g->current_piece.y + 1;
        g->frame = 0;
        colision_checker(g);
    }
}

void get_random_piece(Game *g) {
    unsigned int seed = (unsigned int)(clock());
    srand(seed);

    int candidate = rand() % 7;

    char piece;

    switch (candidate) {
        case 0: piece = i_piece.piece; ++i_piece.count; break;
        case 1: piece = t_piece.piece; ++t_piece.count; break;
        case 2: piece = j_piece.piece; ++j_piece.count; break;
        case 3: piece = l_piece.piece; ++l_piece.count; break;
        case 4: piece = s_piece.piece; ++s_piece.count; break;
        case 5: piece = z_piece.piece; ++z_piece.count; break;
        case 6: piece = o_piece.piece; ++o_piece.count; break;
    }
    g->current_piece.piece = piece;
    // current_piece = i_piece.piece;
}

void rotation_checker(Game *g, int new_rotation) {
    int original_table[TABLE_ROWS][TABLE_COLUMNS];
    memcpy(original_table, table, sizeof(table));

    rotation_handler(g, new_rotation);

    for (int i = 0; i < TABLE_ROWS; i++) {
        for (int j = 0; j < TABLE_COLUMNS; j++) {
            if (table[i][j] == 1 && original_table[i][j] == 2) {
                rotation_handler(g, - new_rotation);
                memcpy(table, original_table, sizeof(table));
            }
        }
    }
}

void rotation_handler(Game *g, int new_rotation) {
    g->current_piece.rotation = g->current_piece.rotation + new_rotation;
    switch (g->current_piece.piece) {
        case 'i':
            if(g->current_piece.rotation + new_rotation == -1) {
                g->current_piece.rotation = 2;
            }
            else if(g->current_piece.rotation + new_rotation == 4) {
                g->current_piece.rotation = 1;
            }
            break;
        case 'o': 
            g->current_piece.rotation = 1;
            break;
        case 't': 
            if(g->current_piece.rotation + new_rotation == -1) {
                g->current_piece.rotation = 4;
            }
            else if(g->current_piece.rotation + new_rotation == 6) {
                g->current_piece.rotation = 1;
            }
            break;
        case 'j': 
            if(g->current_piece.rotation + new_rotation == -1) {
                g->current_piece.rotation = 4;
            }
            else if(g->current_piece.rotation + new_rotation == 6) {
                g->current_piece.rotation = 1;
            }
            break;
        case 'l': 
            if(g->current_piece.rotation + new_rotation == -1) {
                g->current_piece.rotation = 4;
            }
            else if(g->current_piece.rotation + new_rotation == 6) {
                g->current_piece.rotation = 1;
            }
            break;
        case 'z': 
            if(g->current_piece.rotation + new_rotation == -1) {
                g->current_piece.rotation = 2;
            }
            else if(g->current_piece.rotation + new_rotation == 4) {
                g->current_piece.rotation = 1;

            }
            break;
        case 's': 
            if(g->current_piece.rotation + new_rotation == -1) {
                g->current_piece.rotation = 2;
            }
            else if(g->current_piece.rotation + new_rotation == 4) {
                g->current_piece.rotation = 1;
            }
            break;
    }
}

enum direction {
    LEFT,
    DOWN,
    RIGHT
};

void check_valid_movement(Game *g, int direction) {
    switch (direction) {
        case LEFT:
            for (int j = 0; j <= TABLE_COLUMNS; j++) {
                for (int i = 0; i <= TABLE_ROWS; i++) {
                    if (table[i][j] == 1) {
                        if (table[i][j - 1] <= 1) {
                            g->current_piece.x --;
                            return;
                        }
                        else{
                            return;
                        }
                    }
                }
            }
        break;
        case RIGHT:
            for (int j = TABLE_COLUMNS; j <= TABLE_COLUMNS; j--) {
                for (int i = 0; i <= TABLE_ROWS; i++) {
                    if (table[i][j] == 1) {
                        if (table[i][j + 1] <= 1) {
                            g->current_piece.x ++;
                            return;
                        }
                        else{
                            return;
                        }
                    }
                }
            }
        break;
        case DOWN:
            g->current_piece.y ++;
            colision_checker(g);
    }
}

void input_handler(Game *g) {
    // current_piece = t_piece.piece;
    char ch = getch();

    if(ch == 'q') {
        g->running = false;
    }
    else if(ch == 'j') {
        rotation_checker(g, - 1);
    }
    else if(ch == 'k') {
        rotation_checker(g, 1);
    }
    else if(ch == 'a') {
        // current_x--;
        check_valid_movement(g, LEFT);
    }
    else if(ch == 'd') {
        check_valid_movement(g, RIGHT);
    }
    else if(ch == 's') {
        check_valid_movement(g, DOWN);
    }
}

void draw_table() {
    for(int i = 1; i < 21; i++) {
        for(int j = 1; j < 11; j++) {
            if(table[i][j] == 0) {
                printw(" .");
            }
            else if(table[i][j] == 1 || table[i][j] == 2) {
                printw("[]");
            }
        }
        printw("\n");
    }
}

void draw_piece(Game *g) {

    //clear previous piece
    for (int i = 0; i <= TABLE_ROWS; i++) {
        for (int j = 0; j <= TABLE_COLUMNS; j++) {
            if (table[i][j] == 1) {
                table[i][j] = 0;
            }
        }
    }

    int array[4][4];
    int n = (sizeof(i_piece.array) / sizeof(i_piece.array[0]) * sizeof(i_piece.array[0]));

    switch (g->current_piece.piece) {
        case 'i': memcpy(array, i_piece.array, n); break;
        case 'o': memcpy(array, o_piece.array, n); break;
        case 't': memcpy(array, t_piece.array, n); break;
        case 'j': memcpy(array, j_piece.array, n); break;
        case 'l': memcpy(array, l_piece.array, n); break;
        case 's': memcpy(array, s_piece.array, n); break;
        case 'z': memcpy(array, z_piece.array, n); break;
    }
    int piece_size;
    if (g->current_piece.piece == 'i' || g->current_piece.piece == 'o') {
        piece_size = 3;
    }
    else{
        piece_size = 2;
    }

    if (g->current_piece.rotation == 1) {
        for(int i = 0; i <= piece_size; i++) {
            for(int j = 0; j <= piece_size; j++) {
                if(array[i][j] == 1) {
                    table[i + g->current_piece.y][j + g->current_piece.x] = 1;
                }
            }
            printw("\n");
        }
    }
    else if (g->current_piece.rotation == 2) {
        for (int i = 0; i <= piece_size; i++) {
            for (int j = 0; j <= piece_size; j++) {
                if (array[j][i] == 1) {
                    table[i + g->current_piece.y][(piece_size - j) + g->current_piece.x] = 1;
                }
            }
        }
    }
    else if (g->current_piece.rotation == 3) {
        for (int i = 0; i <= piece_size; i++) {
            for (int j = 0; j <= piece_size; j++) {
                if (array[j][i] == 1) {
                    table[(piece_size - j) + g->current_piece.y][(piece_size - i) + g->current_piece.x] = 1;
                }
            }
            printw("\n");
        }
    }
    else if (g->current_piece.rotation == 4) {
        for(int i = piece_size; i >= 0; i--) {
            for(int j = 0; j <= piece_size; j++) {
                if(array[j][i] == 1) {
                    table[(piece_size - i) + g->current_piece.y][j + g->current_piece.x] = 1;
                }
            }
            printw("\n");
        }
    }
}


