#ifndef ASSETS_H
#define ASSETS_H

#include <stdint.h>

#define ROWS 23
#define COLS 13

#define EMPTY 0
#define TILE 1

#define OFFSET 2

#define EMPTY_TILE " ."
#define FILLED_TILE "[]"

typedef struct {
    int tiles[ROWS][COLS];
} Table;

extern void table_init(Table *t);

typedef struct {
    int array[4][4];
    int table[ROWS][COLS];
    char piece;
    uint8_t rotation;
    uint8_t x;
    uint8_t y;
} Piece;

extern void set_piecearr(Piece *p, char piece);

#endif // ASSETS_H
