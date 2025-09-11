#include <ncurses.h>
#include <stdbool.h>
#include "./game.h"

int tick = 0;

int main(){
    WINDOW* win = initscr();
    raw();
    nodelay(win, true);
    curs_set(0);
    noecho();

    while(running == true){
        get_random_piece();
        draw_table();
        draw_piece(current_piece);
        falling_handler();
        refresh();
        input_handler();
        erase();

        tick ++;
    }

    endwin();
    return 0;
}
