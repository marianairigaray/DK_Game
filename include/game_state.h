#ifndef GAME_STATE
#define GAME_STATE

#include "player.h"
#include "enemy.h"
#include "map.h"
#include <stdbool.h>

typedef enum 
{
    MENU,
    NEW_GAME,
    PLAYING,
    PAUSED,
    GAME_OVER,
    EXIT
} Game_state;

void reset_game(char map[MAP_ROWS][MAP_COLS], int current_level, Player *player, Enemy enemies[MAX_ENEMIES], int *enemy_count);
void load_level(int level_num, char map[MAP_ROWS][MAP_COLS], Player *player, Enemy enemies[MAX_ENEMIES], int *enemy_count, bool keep_lives);

#endif