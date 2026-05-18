#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "enemy.h"
#include "map.h"
#include "player.h"

int main(void)
{
    // Inicializa a semente para geração de números aleatórios
    srand(time(NULL));

    char map[MAP_ROWS][MAP_COLS] = {0};

    InitWindow(MAP_COLS * TILE_SIZE, MAP_ROWS * TILE_SIZE, "DK Game");
    SetTargetFPS(60);

    read_map(map, 0);

    Player player = create_player(map);

    // Creates enemies array
    Enemy enemies[MAX_ENEMIES] = {0};
    int enemy_count = 0;
    create_enemies(enemies, map, &enemy_count);

    // Debug information
    printf("Player row = %d, col = %d\n", player.row, player.col);
    for (int i = 0; i < enemy_count; i++)
    {
        printf("Enemy %d row = %d, col = %d\n", i+1, enemies[i].row, enemies[i].col);
        printf("Direction = %d\n", enemies[i].direction);
    }

    while (!WindowShouldClose())
    {
        update_player(&player, map);
        move_enemies(enemies, enemy_count);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw_map(map);
        draw_player(player);
        draw_enemies(enemies, enemy_count);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}