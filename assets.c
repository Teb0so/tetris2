#include <string.h>
#include "assets.h"

void table_init(Table *t) {
    const int TILES[ROWS][COLS] = {
        //     | First visible Column     | Last visible Column
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},// First visible row
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},// Last visible row
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    memcpy(t->tiles, TILES, sizeof(TILES));
}

void set_piecearr(Piece *p, char piece) {
    const int PIECE_I[4][4] = {
        {0, 0, 0, 0,},
        {0, 0, 0, 0,},
        {1, 1, 1, 1,},
        {0, 0, 0, 0,}
    };
    const int PIECE_T[4][4] = {
        {0, 0, 0, 0,},
        {1, 1, 1, 0,},
        {0, 1, 0, 0,},
        {0, 0, 0, 0,}
    };
    const int PIECE_O[4][4] = {
        {0, 0, 0, 0,},
        {0, 1, 1, 0,},
        {0, 1, 1, 0,},
        {0, 0, 0, 0,}
    };
    const int PIECE_J[4][4] = {
        {0, 0, 0, 0,},
        {1, 1, 1, 0,},
        {0, 0, 1, 0,},
        {0, 0, 0, 0,}
    };
    const int PIECE_L[4][4] = {
        {0, 0, 0, 0,},
        {1, 1, 1, 0,},
        {1, 0, 0, 0,},
        {0, 0, 0, 0,}
    };
    const int PIECE_S[4][4] = {
        {0, 0, 0, 0,},
        {0, 1, 1, 0,},
        {1, 1, 0, 0,},
        {0, 0, 0, 0,}
    };
    const int PIECE_Z[4][4] = {
        {0, 0, 0, 0,},
        {1, 1, 0, 0,},
        {0, 1, 1, 0,},
        {0, 0, 0, 0,}
    };
    switch(piece) {
        case 'i': memcpy(p->array, PIECE_I, sizeof(PIECE_T)); break;
        case 'o': memcpy(p->array, PIECE_O, sizeof(PIECE_O)); break;
        case 't': memcpy(p->array, PIECE_T, sizeof(PIECE_T)); break;
        case 'j': memcpy(p->array, PIECE_J, sizeof(PIECE_J)); break;
        case 'l': memcpy(p->array, PIECE_L, sizeof(PIECE_L)); break;
        case 's': memcpy(p->array, PIECE_S, sizeof(PIECE_S)); break;
        case 'z': memcpy(p->array, PIECE_Z, sizeof(PIECE_Z)); break;
    }
}
