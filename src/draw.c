#include <curses.h>
#include <stdbool.h>
#include <unistd.h>
#include "draw.h"
#include "game.h"

int draw_getinput() {
    int ch = getch();
    return ch;
};

void draw_begin(Window *w) {
    WINDOW* win = initscr();
    raw();
    nodelay(win, TRUE);
    curs_set(0);
    noecho();
    getmaxyx(win, w->rows, w->cols);
}

void draw_end() {
    endwin();
}

void draw(Game g, Window w) {
    erase();

    draw_table(g, w);
    draw_stats(g, w);
    draw_statsl(g, w);

    refresh();
}

void draw_table(Game g, Window w) {
    int x_offset = (w.cols / 2) - (GAME_WIDTH / 2);
    int y_offset = (w.rows / 2) - (GAME_HEIGHT / 2);

    for(int i = OFFSET; i < ROWS - 1; i++) {
        for(int j = OFFSET; j < COLS - 1; j++) {
            if (g.paused) {
                mvprintw(y_offset + (i - OFFSET), x_offset + 18 + (j*2 - OFFSET - 2), FILLED_TILE);
            }
            else if(g.table.tiles[i][j] == EMPTY && g.piece.table[i][j] == EMPTY) {
                mvprintw(y_offset + (i - OFFSET), x_offset + 18 + (j*2 - OFFSET - 2), EMPTY_TILE);
            }
            else if(g.table.tiles[i][j] == TILE || g.piece.table[i][j] == TILE) {
                mvprintw(y_offset + (i - OFFSET), x_offset + 18 + (j*2 - OFFSET - 2), FILLED_TILE);
            }
        }
    }
}
void draw_statsl(Game g, Window w) {
    int x_offset = (w.cols / 2) - (GAME_WIDTH / 2);
    int y_offset = (w.rows / 2) - (GAME_HEIGHT / 2);

    mvprintw(y_offset, x_offset, "Statistics:");

    mvprintw(y_offset + 2, x_offset + 1, L1_PREVIEW_T);
    mvprintw(y_offset + 3, x_offset + 1, L2_PREVIEW_T);

    mvprintw(y_offset + 5, x_offset + 1, L1_PREVIEW_J);
    mvprintw(y_offset + 6, x_offset + 1, L2_PREVIEW_J);

    mvprintw(y_offset + 7, x_offset + 1, L1_PREVIEW_Z);
    mvprintw(y_offset + 8, x_offset + 1, L2_PREVIEW_Z);

    mvprintw(y_offset + 10, x_offset + 1, L1_PREVIEW_O);
    mvprintw(y_offset + 11, x_offset + 1, L2_PREVIEW_O);

    mvprintw(y_offset + 13, x_offset + 1, L1_PREVIEW_S);
    mvprintw(y_offset + 14, x_offset + 1, L2_PREVIEW_S);

    mvprintw(y_offset + 16, x_offset + 1, L1_PREVIEW_L);
    mvprintw(y_offset + 17, x_offset + 1, L2_PREVIEW_L);

    mvprintw(y_offset + 19, x_offset + 1, L2_PREVIEW_I);

    mvprintw(y_offset + 3, x_offset + 11, "%d", g.score.t);
    mvprintw(y_offset + 6, x_offset + 11, "%d", g.score.j);
    mvprintw(y_offset + 8, x_offset + 11, "%d", g.score.z);
    mvprintw(y_offset + 11, x_offset + 11, "%d", g.score.o);
    mvprintw(y_offset + 14, x_offset + 11, "%d", g.score.s);
    mvprintw(y_offset + 17, x_offset + 11, "%d", g.score.l);
    mvprintw(y_offset + 19, x_offset + 11, "%d", g.score.i);
}

void draw_stats(Game g, Window w) {
    int x_offset = (w.cols / 2) - (GAME_WIDTH / 2);
    int y_offset = (w.rows / 2) - (GAME_HEIGHT / 2);

    const int offset = 42;

    mvprintw(y_offset + 0, x_offset + offset, "Next:");

    if (g.preview) {
        switch(g.piece.next) {
            case 'i':
                mvprintw(y_offset + 2, x_offset + offset, L1_PREVIEW_I);
                mvprintw(y_offset + 3, x_offset + offset, L2_PREVIEW_I);
                break;
            case 'o':
                mvprintw(y_offset + 2, x_offset + offset, L1_PREVIEW_O);
                mvprintw(y_offset + 3, x_offset + offset, L2_PREVIEW_O);
                break;
            case 't':
                mvprintw(y_offset + 2, x_offset + offset, L1_PREVIEW_T);
                mvprintw(y_offset + 3, x_offset + offset, L2_PREVIEW_T);
                break;
            case 'j':
                mvprintw(y_offset + 2, x_offset + offset, L1_PREVIEW_J);
                mvprintw(y_offset + 3, x_offset + offset, L2_PREVIEW_J);
                break;
            case 'l':
                mvprintw(y_offset + 2, x_offset + offset, L1_PREVIEW_L);
                mvprintw(y_offset + 3, x_offset + offset, L2_PREVIEW_L);
                break;
            case 's':
                mvprintw(y_offset + 2, x_offset + offset, L1_PREVIEW_S);
                mvprintw(y_offset + 3, x_offset + offset, L2_PREVIEW_S);
                break;
            case 'z':
                mvprintw(y_offset + 2, x_offset + offset, L1_PREVIEW_Z);
                mvprintw(y_offset + 3, x_offset + offset, L2_PREVIEW_Z);
                break;
        }
    }

    mvprintw(y_offset + 5, x_offset + offset, "Level: %d", g.score.level);
    mvprintw(y_offset + 6, x_offset + offset, "Lines: %d", g.score.lines);
    mvprintw(y_offset + 7, x_offset + offset, "Score: %d", g.score.score);
    if (g.paused) mvprintw(y_offset + 9, x_offset + offset, "PAUSED");
    mvprintw(y_offset + 11, x_offset + offset, "'q'     - Quit");
    mvprintw(y_offset + 12, x_offset + offset, "'n'     - Toggle preview");
    mvprintw(y_offset + 13, x_offset + offset, "'j/k'   - Rotate");
    mvprintw(y_offset + 14, x_offset + offset, "'a/d'   - Move left/right");
    mvprintw(y_offset + 15, x_offset + offset, "'s'     - Soft drop");
    mvprintw(y_offset + 16, x_offset + offset, "'Space' - Hard drop");
    mvprintw(y_offset + 17, x_offset + offset, "'p'     - Toggle pause");
}
