#include "points.h"
#include <stdbool.h>
#include "raylib.h"

#define POINT_VALUE 10

// Apaga os pontos já coletados pelo players
static void clear_point(char map[MAP_ROWS][MAP_COLS], int col, int row)
{
    map[row][col] = ' ';
}

// Verifica se o player colidiu com um ponto (essa função é chamada para os 4 cantos do player) 
static bool is_point_at_pixel(char map[MAP_ROWS][MAP_COLS], int col, int row)
{
    return map[row][col] == 'X';
}

// Verifica se o player coletou um ponto
static bool is_point(char map[MAP_ROWS][MAP_COLS], float x, float y, int *point_col, int *point_row) {

    // Calculo das quatro bordas atuais do player
    int top_border = (int) y / TILE_SIZE;
    int lower_border = (int) (y + TILE_SIZE-1) / TILE_SIZE;
    int left_border = (int) x / TILE_SIZE;
    int right_border = (int) (x + TILE_SIZE-1) / TILE_SIZE;

    // Verifica se o player colidiu com um ponto para suas quatro bordas
    if(is_point_at_pixel(map, left_border, top_border)) 
    {
        *point_col = left_border;
        *point_row = top_border;
        return true;
    }

    if(is_point_at_pixel(map, left_border, lower_border))
    {
        *point_col = left_border;
        *point_row = lower_border;
        return true;
    }

    if(is_point_at_pixel(map, right_border, top_border))
    {
        *point_col = right_border;
        *point_row = top_border;
        return true;
    }
    
    if(is_point_at_pixel(map, right_border, lower_border))
    {
        *point_col = right_border;
        *point_row = lower_border;
        return true;
    }

    // Caso não encontre, retorna falso
    return false;
}

void update_points(char map[MAP_ROWS][MAP_COLS], Player *player)
{
    int point_col, point_row;

    if (is_point(map, player->x, player->y, &point_col, &point_row))
    {
        player->points += POINT_VALUE;
        clear_point(map, point_col, point_row);
    }
}

void draw_points(Player *player)
{
    DrawText(TextFormat("Points: %d", player->points), 100, 10, 20, BLACK);
}