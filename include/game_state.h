#ifndef GAME_STATE
#define GAME_STATE

#include "player.h"
#include "enemy.h"
#include "map.h"
#include "ranking.h"
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

typedef enum Game_over_states
{
    GAME_OVER_SCREEN,
    INPUT_NAME,
    VIEW_RANKING
} Game_over_states;

typedef struct Game_Save
{
    int score;
    int lives;
    int current_level;
    bool game_active;
} Game_Save;

bool has_active_game();
void reset_game(char map[MAP_ROWS][MAP_COLS], int current_level, Player *player, Enemy enemies[MAX_ENEMIES], int *enemy_count);
void load_level(int level_num, char map[MAP_ROWS][MAP_COLS], Player *player, Enemy enemies[MAX_ENEMIES], int *enemy_count, bool keep_lives);
void game_over(Game_over_states *game_over_state, Ranking ranking[MAX_RANKING_ENTRIES], int *ranked_players, int score);
void draw_game_over();

#endif