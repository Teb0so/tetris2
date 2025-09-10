#include <ncurses.h>
#include <stdbool.h>
#include "./game.h"

char current_piece;
int tick = 0;

int main(){
    initscr();
    raw();
    curs_set(0);
    noecho();

    while(running == true){

        draw_table();
        draw_piece(current_piece);
        falling_handler();
        refresh();
        input_handler();
        clear();

        tick ++;
    }

    endwin();
    return 0;
}
