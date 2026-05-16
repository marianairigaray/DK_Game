#include <stdio.h>
#include "raylib.h"
#include "map.h"
#include "player.h"

int main(void)
{
    char map[MAP_ROWS][MAP_COLS] = {0};

    InitWindow(MAP_COLS * TILE_SIZE, MAP_ROWS * TILE_SIZE, "DK Game");
    SetTargetFPS(60);

    read_map(map, 0);

    Player player = create_player(map);

    printf("Player row = %d, col = %d\n", player.row, player.col);

    while (!WindowShouldClose())
    {
        update_player(&player, map);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        draw_map(map);
        draw_player(player);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}