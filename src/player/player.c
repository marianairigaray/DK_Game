#include "raylib.h"
#include "player.h"
#include "map.h"

static int is_solid_tile(char map[MAP_ROWS][MAP_COLS], int row, int col)
{
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS)
    {
        return 1;
    }

    return map[row][col] == 'Z';
}

static int is_solid_at_pixel(char map[MAP_ROWS][MAP_COLS], float x, float y)
{
    int col = (int)(x / TILE_SIZE);
    int row = (int)(y / TILE_SIZE);

    return is_solid_tile(map, row, col);
}

static int can_move_to(char map[MAP_ROWS][MAP_COLS], float x, float y, float width, float height)
{
    // Verifica os 4 cantos do player
    if (is_solid_at_pixel(map, x, y))
    {
        return 0;
    }

    if (is_solid_at_pixel(map, x + width - 1, y))
    {
        return 0;
    }

    if (is_solid_at_pixel(map, x, y + height - 1))
    {
        return 0;
    }

    if (is_solid_at_pixel(map, x + width - 1, y + height - 1))
    {
        return 0;
    }

    return 1;
}

Player create_player(char map[MAP_ROWS][MAP_COLS])
{
    Player player;

    player.x = 0;
    player.y = 0;
    player.width = TILE_SIZE;
    player.height = TILE_SIZE;
    player.speed = 180.0f;

    for (int row = 0; row < MAP_ROWS; row++)
    {
        for (int col = 0; col < MAP_COLS; col++)
        {
            if (map[row][col] == 'P')
            {
                player.x = col * TILE_SIZE;
                player.y = row * TILE_SIZE;

                // Remove o P do mapa fixo
                map[row][col] = ' ';

                return player;
            }
        }
    }

    return player;
}

void update_player(Player *player, char map[MAP_ROWS][MAP_COLS])
{
    float dt = GetFrameTime();

    float dx = 0.0f;
    float dy = 0.0f;

    if (IsKeyDown(KEY_RIGHT))
    {
        dx += player->speed * dt;
    }

    if (IsKeyDown(KEY_LEFT))
    {
        dx -= player->speed * dt;
    }

    if (IsKeyDown(KEY_UP))
    {
        dy -= player->speed * dt;
    }

    if (IsKeyDown(KEY_DOWN))
    {
        dy += player->speed * dt;
    }

    // Move no eixo X primeiro
    if (can_move_to(map, player->x + dx, player->y, player->width, player->height))
    {
        player->x += dx;
    }

    // Depois move no eixo Y
    if (can_move_to(map, player->x, player->y + dy, player->width, player->height))
    {
        player->y += dy;
    }
}

void draw_player(Player player)
{
    DrawRectangle(
        (int)player.x,
        (int)player.y,
        (int)player.width,
        (int)player.height,
        RED
    );
}