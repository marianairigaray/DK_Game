#ifndef GAME_STATE
#define GAME_STATE

#include "player.h"
#include "enemy.h"
#include "map.h"
#include <stdbool.h>

typedef enum 
{
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    GAME_EXIT
} Game_state;

void load_level(int level_num, char map[MAP_ROWS][MAP_COLS], Player *player, Enemy enemies[MAX_ENEMIES], int *enemy_count, bool keep_lives);

#endif