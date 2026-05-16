#include "collision.h"

int is_valid_move(char map[MAP_ROWS][MAP_COLS], int row, int col)
{
    if(row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS){
        return 0;
    }
    if(map[row][col] == 'Z'){

        return 0;
    }
    return 1;
}   