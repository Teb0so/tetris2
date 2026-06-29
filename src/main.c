#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

#include "game.h"
#include "draw.h"

#define FPS 60
#define FRAME_TIME (1000000000L / FPS)

static void main_loop(Game *g, Window w) {
    struct timespec start, end;
    while(g->running) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        // Game logic

        game_drawpiece(g);
        game_fallpiece(g);
        game_topoutchecker(g);
        game_clearline(g, w);
        game_levelchecker(g);
        game_inputhandler(g);

        draw(*g, w);

        clock_gettime(CLOCK_MONOTONIC , &end);
        long int frame_ns = (end.tv_sec - start.tv_sec) * 1000000000L +
                            (end.tv_nsec - start.tv_nsec);
        if (frame_ns < FRAME_TIME) {
            struct timespec sleep_time;
            sleep_time.tv_sec = 0;
            sleep_time.tv_nsec = FRAME_TIME - frame_ns;
            nanosleep(&sleep_time, NULL);

            if (!g->paused) {
                g->frame ++;
            }
        }
    }
}

int levelselector() {
    char buf[32];

    printf("Enter a level [0-9]: ");
    fgets(buf, sizeof(buf), stdin);

    int level = atoi(buf);

    return level;
}

int main(void) {
    Game g;
    Window w;
    int level;

    setlocale(LC_CTYPE,"C-UTF-8");

    do {
        level = levelselector();
        if (level < 0 || level > 9) {printf("Insert a valid number!\n");}
    } while (level < 0 || level > 9);

    draw_begin(&w);

    if (w.rows < GAME_HEIGHT || w.cols < GAME_WIDTH) {
        printf("[ERROR] terminal to small, resize your terminal to be at least %d X %d\n", GAME_WIDTH, GAME_HEIGHT);
        return 0;
    }

    game_init(&g, level);
    main_loop(&g, w);

    draw_end();

    printf("Score: %d\n", g.score.score);
    return 0;
}
