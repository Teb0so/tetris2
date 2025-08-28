#include <ncurses.h>
#include <stdbool.h>
#include "./game.h"
#include "./assets.h"

char current_piece;

int main(){
    initscr();
    raw();
    curs_set(0);
    noecho();

    while(running == true){
        // draw_table();
        draw_piece(current_piece);
        refresh();
        input_handler();
        clear();
    }

    endwin();
    return 0;
}
