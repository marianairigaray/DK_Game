#ifndef COLLISION_H
#define COLLISION_H

#include "player.h"
#include "enemy.h"
#include "map.h"

// Declaração da função que processará as colisões
void check_player_enemy_collisions(Player *player, Enemy enemies[MAX_ENEMIES], int enemy_count, char map[MAP_ROWS][MAP_COLS]);

#endif