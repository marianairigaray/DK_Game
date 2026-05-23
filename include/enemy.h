#ifndef ENEMY_H
#define ENEMY_H

#include "map.h"

#define MAX_ENEMIES 10
#define ENEMY_SPEED 150

// Enemy movement direction
typedef enum
{
    LEFT = -1,
    RIGHT = 1
} Direction;

typedef struct
{
    // Enemy position (pixels)
    float x;
    float y;
    
    // Enemy movement direction
    Direction direction;
} Enemy;

void create_enemies(Enemy enemy[MAX_ENEMIES], char map[MAP_ROWS][MAP_COLS], int *enemy_count);
void draw_enemies(Enemy enemies[MAX_ENEMIES], int enemy_count);
void move_enemies(char map[MAP_ROWS][MAP_COLS], Enemy enemies[MAX_ENEMIES], int enemy_count);

#endif
