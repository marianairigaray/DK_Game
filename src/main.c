#include "raylib.h"
#include <stdio.h>
#include "map.h"

int main(void)
{
    char map[MAP_ROWS][MAP_COLS] = {0};
    InitWindow(640, 480, "DK Game");
    SetTargetFPS(60);
    read_map(map,0);
    while (!WindowShouldClose())
    {
        BeginDrawing();


        ClearBackground(WHITE);
        draw_map(map);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}