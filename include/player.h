#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

typedef struct
{
    int row;
    int col;
} Player;

Player create_player(char map[MAP_ROWS][MAP_COLS]);
void update_player(Player *player, char map[MAP_ROWS][MAP_COLS]);
void draw_player(Player player);

#endif