#ifndef ASSETS_H
#define ASSETS_H

extern int i_array[4][4];
extern int o_array[4][4];
extern int t_array[3][3];
extern int j_array[3][3];
extern int l_array[3][3];
extern int z_array[3][3];
extern int s_array[3][3];

typedef struct{
    char piece; // I, T, O, J, L, Z, S
    int piece_size;
    int rotation_stages[4];
    int array[4][4];
} Pieces;

extern Pieces i_piece, t_piece, o_piece, j_piece, l_piece, z_piece, s_piece;

#endif //ASSETS_H

