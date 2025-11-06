#include <bits/time.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include "./game.h"

#define FPS 60
#define FRAME_TIME (1000000000L / FPS)

void write_log(Game *g, int stage) {
    FILE *log;
    log = fopen("log.txt", "a");
    fprintf(log, "%d - running = %d\n", stage, g->running);
    fclose(log);
}

int main() {
    Game g;

    game_init(&g);
    bool running = game_get_state(&g);
    write_log(&g, 1);

    WINDOW* win = initscr();
    raw();
    nodelay(win, true);
    curs_set(0);
    noecho();

    struct timespec start, end;

    get_random_piece(&g);
    while(g.running) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        draw_table(&g);
        draw_piece(&g);
        dbg_info(&g);
        falling_handler(&g);
        refresh();
        input_handler(&g);
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

        game_increase_frame(&g);
        write_log(&g, 2);
        running = game_get_state(&g);
    }

    endwin();
    write_log(&g, 3);
    return 0;
}
