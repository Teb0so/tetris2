#include <ncurses.h>
#include <stdbool.h>
#include "./game.h"
#include "./assets.h"

int main(){
    initscr();
    raw();
    curs_set(0);
    noecho();

    while(running == true){
        rotation_handler(t_piece.piece);
        refresh();
        input_handler();
        clear();
    }

    endwin();
    return 0;
}
