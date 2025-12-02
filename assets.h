#ifndef ASSETS_H
#define ASSETS_H

#include <stdint.h>

#define ROWS 23
#define COLS 13

#define EMPTY 0
#define TILE 1

#define OFFSET 2

#define PIECE_AMOUNT 7

#define EMPTY_TILE " ."
#define FILLED_TILE "[]"

#define L1_PREVIEW_I " "
#define L2_PREVIEW_I "[][][][]"

#define L1_PREVIEW_O "  [][]"
#define L2_PREVIEW_O "  [][]"

#define L1_PREVIEW_T " [][][]"
#define L2_PREVIEW_T "   []"

#define L1_PREVIEW_J " [][][]"
#define L2_PREVIEW_J "     []"

#define L1_PREVIEW_L " [][][]"
#define L2_PREVIEW_L " []"

#define L1_PREVIEW_S "   [][]"
#define L2_PREVIEW_S " [][]"

#define L1_PREVIEW_Z " [][]"
#define L2_PREVIEW_Z "   [][]"

typedef struct {
    int tiles[ROWS][COLS];
} Table;

extern void table_init(Table *t);

typedef struct {
    int array[4][4];
    int table[ROWS][COLS];
    char piece;
    char next;
    int8_t rotation;
    uint8_t x;
    uint8_t y;
} Piece;

extern void set_piecearr(Piece *p, char piece);

#endif // ASSETS_H
