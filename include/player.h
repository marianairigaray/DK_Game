#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

typedef struct
{
    float x;
    float y;
    float width;
    float height;
    float speed;
    int row;
    int col;
    int is_grounded;
    int speed_y;
} Player;

Player create_player(char map[MAP_ROWS][MAP_COLS]);
void update_player(Player *player, char map[MAP_ROWS][MAP_COLS]);
void draw_player(Player player);

#endif