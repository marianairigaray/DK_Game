#ifndef ENEMY_H
#define ENEMY_H

#define MAX_ENEMIES 10

#include "map.h"

typedef struct Enemy
{
    // Enemy´s coordenates
    int row;
    int col;
} Enemy;

void create_enemies(Enemy enemy[MAX_ENEMIES], char map[MAP_ROWS][MAP_COLS], int *enemy_count);
void draw_enemies(Enemy enemies[MAX_ENEMIES], int enemy_count);

#endif
