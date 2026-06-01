#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

typedef enum
{
    GROUNDED,   // Estado padrão (parado ou andando sobre a plataforma)
    AIRBORNE,   // No ar (pulando ou caindo)
    CLIMBING    // Na escada
} States;

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
    States state;
    int lives;
    float spawn_x;
    float spawn_y;

} Player;

Player create_player(char map[MAP_ROWS][MAP_COLS]);
void update_player(Player *player, char map[MAP_ROWS][MAP_COLS]);
void draw_player(Player player);
void save_game_lives(int lives);
int load_game_lives(int default_lives);

#endif