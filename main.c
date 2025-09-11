#include <ncurses.h>
#include <stdbool.h>
#include "./game.h"

int tick = 0;

void tick_dbg(){
    printw("tick: %d", tick);
}

int main(){
    WINDOW* win = initscr();
    raw();
    nodelay(win, true);
    curs_set(0);
    noecho();

    get_random_piece();
    while(running == true){
        draw_table();
        draw_piece(current_piece);
        tick_dbg();
        falling_handler();
        refresh();
        input_handler();
        erase();

        tick ++;
    }

    endwin();
    return 0;
}
