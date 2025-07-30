#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

extern bool running;
extern int rotation;
extern char ch;

extern void input_handler();
extern void rotation_handler(char piece);

#endif //GAME_H
