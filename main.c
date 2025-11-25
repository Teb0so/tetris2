#include <curses.h>
#include <stdbool.h>
#include <time.h>

#include "game.h"

#define FPS 60
#define FRAME_TIME (1000000000L / FPS)

static void main_loop(Game *g)
{
    struct timespec start, end;
    while(g->running) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        // Game logic
        erase();

        game_drawpiece(g);
        game_fallpiece(g);
        game_drawtable(g);
        game_clearline(g);
        game_inputhandler(g);

        refresh();

        clock_gettime(CLOCK_MONOTONIC , &end);
        long int frame_ns = (end.tv_sec - start.tv_sec) * 1000000000L +
                            (end.tv_nsec - start.tv_nsec);
        if (frame_ns < FRAME_TIME) {
            struct timespec sleep_time;
            sleep_time.tv_sec = 0;
            sleep_time.tv_nsec = FRAME_TIME - frame_ns;
            nanosleep(&sleep_time, NULL);

        g->frame ++;
        }
    }
}

int main(void)
{
    Game g;

    WINDOW* win = initscr();
    raw();
    nodelay(win, TRUE);
    curs_set(0);
    noecho();

    game_init(&g);
    main_loop(&g);

    endwin();
    return 0;
}
