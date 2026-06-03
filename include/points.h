#ifndef POINTS_H
#define POINTS_H

#include "map.h"
#include "player.h"

void update_points(char map[MAP_ROWS][MAP_COLS], Player *player);
void draw_points(Player *player);

#endif