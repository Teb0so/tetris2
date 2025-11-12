#ifndef ASSETS_H
#define ASSETS_H

#define ROWS 22
#define COLS 12

#define EMPTY 0
#define TILE 1

#define EMPTY_TILE " ."
#define FILLED_TILE "[]"

typedef struct {
    int tiles[ROWS][COLS];
} Table;

void table_init(Table *t);

#endif // ASSETS_H
