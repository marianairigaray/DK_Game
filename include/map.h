#ifndef MAP_H
#define MAP_H

#define MAP_ROWS 30
#define MAP_COLS 30
#define TILE_SIZE 20
#define SCREEN_WIDTH (MAP_COLS * TILE_SIZE)
#define SCREEN_HEIGHT (MAP_ROWS * TILE_SIZE)

void read_map(char map[MAP_ROWS][MAP_COLS], int num_map);
void draw_map(char map[MAP_ROWS][MAP_COLS]);

#endif