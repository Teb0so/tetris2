#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "main.h"
#include "./game.h"
#include "./assets.h"


char current_piece;
bool running = true;
int rotation = 1;

int current_y = 0;
int current_x = 4;

int table[TABLE_ROWS][TABLE_COLUMNS] = {
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
};

void add_piece(){
    for (int i = 0; i <= TABLE_ROWS; i++) {
        for (int j = 0; j <= TABLE_COLUMNS; j++) {
            if (table[i][j] == 1) {
                table[i][j] = 2;
            }
        }
    }
}

void colision_checker(){
    for (int i = 0; i <= TABLE_ROWS; i++) {
        for (int j = 0; j <= TABLE_COLUMNS; j++) {
            if (table[i][j] == 1) {
                if (table[i + 1][j] == 2){
                    add_piece();
                    current_y = 0;
                    current_x = 4;
                }
            }
        }
    }
    rotation = 1;
}

void falling_handler(){
    if(tick == 90000){
        current_y = current_y + 1;
        tick = 0;
    }
}

char get_random_piece(){
    srand(time(NULL));

    int candidate = rand() % 7;

    char piece;

    switch (candidate) {
        case 0: piece = i_piece.piece; break;
        case 1: piece = t_piece.piece; break;
        case 2: piece = j_piece.piece; break;
        case 3: piece = l_piece.piece; break;
        case 4: piece = s_piece.piece; break;
        case 5: piece = z_piece.piece; break;
        case 6: piece = o_piece.piece; break;
    }
    return piece;
}

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
    if(current_y == 0){
        current_piece = get_random_piece();
        current_y ++;
    }
    // current_piece = t_piece.piece;
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
    else if(ch == 'a'){
        current_x--;
    }
    else if(ch == 'd'){
        current_x++;
    }
    else if(ch == 's'){
        current_y++;
    }
}

void draw_table(){
    for(int i = 1; i < 21; i++){
        for(int j = 1; j < 11; j++){
            if(table[i][j] == 0){
                printw(" .");
            }
            else if(table[i][j] == 1 || table[i][j] == 2){
                printw("[]");
            }
        }
        printw("\n");
    }
}

void draw_piece(char piece){

    //clear previous piece
    for (int i = 0; i <= TABLE_ROWS; i++) {
        for (int j = 0; j <= TABLE_COLUMNS; j++) {
            if (table[i][j] == 1) {
                table[i][j] = 0;
            }
        }
    }

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
                if(array[i][j] == 1){
                    table[i + current_y][j + current_x] = 1;
                }
            }
            printw("\n");
        }
    }
    else if (rotation == 2) {
        for (int i = 0; i <= piece_size; i++) {
            for (int j = 0; j <= piece_size; j++) {
                if (array[j][i] == 1) {
                    table[i + current_y][(piece_size - j) + current_x] = 1;
                }
            }
        }
    }
    else if (rotation == 3) {
        for (int i = 0; i <= piece_size; i++) {
            for (int j = 0; j <= piece_size; j++) {
                if (array[j][i] == 1) {
                    table[(piece_size - j) + current_y][i + current_x] = 1;
                }
            }
            printw("\n");
        }
    }
    else if (rotation == 4) {
        for(int i = piece_size; i >= 0; i--){
            for(int j = 0; j <= piece_size; j++){
                if(array[j][i] == 1){
                    table[i + current_y][j + current_x] = 1;
                }
            }
            printw("\n");
        }
    }
    colision_checker();
}


