#include "enemy.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "map.h"

void create_enemies(Enemy enemies[MAX_ENEMIES], char map[MAP_ROWS][MAP_COLS], int *enemy_count)
{
    for (int row = 0; row < MAP_ROWS; row++)
    {
        for (int col = 0; col < MAP_COLS; col++)
        {
            if (map[row][col] == 'E')
            {
                // Caso existam mais inimigos que o máximo, a função retorna com mensagem de erro
                if (*enemy_count >= MAX_ENEMIES)
                {
                    printf("Error: maximum number of enemies exceeded.\n");
                    return;
                }

                // Guarda a posição inicial do inimigo atual
                enemies[*enemy_count].x = col * TILE_SIZE; 
                enemies[*enemy_count].y = row * TILE_SIZE;

                // Retira a letra 'E' do mapa e substituí por espaço em branco para evitar conflitos
                map[row][col] = ' ';

                // Inicializa a direção de movimento do inimigo aleatóriamente
                if (rand() % 2)
                    enemies[*enemy_count].direction = RIGHT;
                else
                    enemies[*enemy_count].direction = LEFT;

                (*enemy_count)++;
            }
        }
    }
}

void draw_enemies(Enemy enemies[MAX_ENEMIES], int enemy_count)
{
    for (int i = 0; i < enemy_count; i++)
        DrawRectangleV((Vector2){enemies[i].x, enemies[i].y}, (Vector2){TILE_SIZE, TILE_SIZE}, ORANGE);
}

// Verifica se o próximo movimento do inimigo é válido
static bool is_valid_move(char map[MAP_ROWS][MAP_COLS], float x, float y)
{
    int row = (int) y / TILE_SIZE;
    int left_border = (int) x / TILE_SIZE;
    int right_border = (int) (x + TILE_SIZE-1) / TILE_SIZE;

    // Caso ultrapasse a borda horizontal esquerda
    if (x < 0)
        return false;

    // Caso ultrapasse a borda horizontal direita
    if (x + TILE_SIZE > SCREEN_WIDTH)
        return false;

    // Caso não exista chão embaixo a direita
    if (map[row + 1][right_border] == ' ')
        return false;

    // Caso não exista chão embaixo a esquerda
    if (map[row + 1][left_border] == ' ')
        return false;

    return true;
}

void move_enemies(char map[MAP_ROWS][MAP_COLS], Enemy enemies[MAX_ENEMIES], int enemy_count)
{
    float frame_time = GetFrameTime();

    // Calcula a variação de x do frame atual 
    float delta_x = ENEMY_SPEED * frame_time;

    for (int i = 0; i < enemy_count; i++)
    {
        // Calcula a nova posição do inimigo somando ou subtraindo delta_x da posição atual, dependendo da direção do movimento
        float new_x = enemies[i].x + (delta_x * enemies[i].direction);

        if (is_valid_move(map, new_x,  enemies[i].y))
        {
            enemies[i].x = new_x;
        }
        else
        {
            enemies[i].direction *= -1; // Toggle na direção

            // Recalcula a nova posição
            enemies[i].x += (delta_x * enemies[i].direction);
        }
    }
}