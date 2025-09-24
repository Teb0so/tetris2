#include <bits/time.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include "./game.h"

#define FPS 60
#define FRAME_TIME (1000000000L / FPS)

int main() {
    WINDOW* win = initscr();
    raw();
    nodelay(win, true);
    curs_set(0);
    noecho();

    struct timespec start, end;

    get_random_piece();
    while(running) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        draw_table();
        draw_piece(current_piece);
        dbg_info();
        falling_handler();
        refresh();
        input_handler();
        erase();

        clock_gettime(CLOCK_MONOTONIC, &end);
        long int frame_ns = (end.tv_sec - start.tv_sec) * 1000000000L +
                            (end.tv_nsec - start.tv_nsec);

        if (frame_ns < FRAME_TIME) {
            struct timespec sleep_time;
            sleep_time.tv_sec = 0;
            sleep_time.tv_nsec = FRAME_TIME - frame_ns;
            nanosleep(&sleep_time, NULL);
        }

        frame++;
    }

    endwin();
    return 0;
}
