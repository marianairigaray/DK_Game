#include "player.h"
#include <stdio.h>
#include "map.h"
#include "raylib.h"

Player create_player(char map[MAP_ROWS][MAP_COLS])
{
    Player player = {0, 0};
    for(int i = 0; i < MAP_ROWS; i++)
    {
        for(int j = 0; j < MAP_COLS; j++)
        {
            if(map[i][j] == 'P')
            {
                player.row = i;
                player.col = j;
                map[i][j] = ' ';
                return player;
            }
        }
    }
    return player;
}
static int is_valid_move(char map[MAP_ROWS][MAP_COLS], int row, int col)
{
    if(row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS){
        return 0;
    }
    if(map[row][col] == 'Z'){

        return 0;
    }
    return 1;
}
void update_player(Player *player, char map[MAP_ROWS][MAP_COLS])
{
    int new_row = player->row;
    int new_col = player->col;
    
    
    if (IsKeyPressed(KEY_UP)){        
        new_row--;
    }
    else if (IsKeyPressed(KEY_DOWN)){
        new_row++;
    }
    else if (IsKeyPressed(KEY_LEFT)){
        new_col--;
    }
    else if (IsKeyPressed(KEY_RIGHT)){
        new_col++;
    }
    
    if (is_valid_move(map, new_row, new_col))
    {   
        player->row = new_row;
        player->col = new_col;
    }
}
void draw_player(Player player){
    DrawRectangle(player.col * TILE_SIZE, player.row * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED);
}