#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include "./game.h"
#include "./assets.h"

// int array[3][3] = {
//     {0, 0, 0,},
//     {1, 1, 1,},
//     {0, 0, 1,}
// };

bool running = true;
int rotation = 1;

void rotation_handler(char piece, int new_rotation){
    rotation = rotation + new_rotation;
    switch (piece) {
        case 'i':
            if(rotation + new_rotation == -1){
                rotation = 2;
            }
            else if(rotation + new_rotation == 4){
                rotation = 1;
            }
            break;
        case 'o': 
            rotation = 1;
            break;
        case 't': 
            if(rotation + new_rotation == -1){
                rotation = 4;
            }
            else if(rotation + new_rotation == 6){
                rotation = 1;
            }
            break;
        case 'j': 
            if(rotation + new_rotation == -1){
                rotation = 4;
            }
            else if(rotation + new_rotation == 6){
                rotation = 1;
            }
            break;
        case 'l': 
            if(rotation + new_rotation == -1){
                rotation = 4;
            }
            else if(rotation + new_rotation == 6){
                rotation = 1;
            }
            break;
        case 'z': 
            if(rotation + new_rotation == -1){
                rotation = 2;
            }
            else if(rotation + new_rotation == 4){
                rotation = 1;
            }
            break;
        case 's': 
            if(rotation + new_rotation == -1){
                rotation = 2;
            }
            else if(rotation + new_rotation == 4){
                rotation = 1;
            }
            break;
    }
}

void input_handler(){
    current_piece = l_piece.piece;
    char ch = getch();

    if(ch == 'q'){
        running = false;
    }
    else if(ch == 'j'){
        rotation_handler(current_piece, - 1);
    }
    else if(ch == 'k'){
        rotation_handler(current_piece, 1);
    }
}

void draw_piece(char piece){

    int array[4][4];
    int n = (sizeof(i_piece.array) / sizeof(i_piece.array[0]) * sizeof(i_piece.array[0]));

    switch (piece) {
        case 'i': memcpy(array, i_piece.array, n); break;
        case 'o': memcpy(array, o_piece.array, n); break;
        case 't': memcpy(array, t_piece.array, n); break;
        case 'j': memcpy(array, j_piece.array, n); break;
        case 'l': memcpy(array, l_piece.array, n); break;
        case 's': memcpy(array, s_piece.array, n); break;
        case 'z': memcpy(array, z_piece.array, n); break;
    }
    int piece_size;
    if (piece == 'i' || piece == 'o'){
        piece_size = 3;
    }
    else{
        piece_size = 2;
    }

    if (rotation == 1) {
        for(int i = 0; i <= piece_size; i++){
            for(int j = 0; j <= piece_size; j++){
                if(array[i][j] == 0){
                    printw("  ");
                }
                else if(array[i][j] == 1){
                    printw("[]");
                }
            }
            printw("\n");
        }
    }
    else if (rotation == 2) {
        for(int i = 0; i <= piece_size; i++){
            for(int j = piece_size; j >= 0; j--){
                if(array[j][i] == 0){
                    printw("  ");
                }
                else if(array[j][i] == 1){
                    printw("[]");
                }
            }
            printw("\n");
        }
    }
    else if (rotation == 3) {
        for(int i = piece_size; i >= 0; i--){
            for(int j = piece_size; j >= 0; j--){
                if(array[i][j] == 0){
                    printw("  ");
                }
                else if(array[i][j] == 1){
                    printw("[]");
                }
            }
            printw("\n");
        }
    }
    else if (rotation == 4) {
        for(int i = piece_size; i >= 0; i--){
            for(int j = 0; j <= piece_size; j++){
                if(array[j][i] == 0){
                    printw("  ");
                }
                else if(array[j][i] == 1){
                    printw("[]");
                }
            }
            printw("\n");
        }
    }
}


