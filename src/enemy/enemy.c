#include "enemy.h"

#include <stdio.h>

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
                if(*enemy_count >= MAX_ENEMIES)
                {
                    printf("Error: maximum number of enemies exceeded.\n");
                    return;
                }

                // Guarda a posição inicial do inimigo atual na struct "enemies" 
                enemies[*enemy_count].row = row;
                enemies[*enemy_count].col = col;

                // Retira a letra 'E' do mapa e substituí por espaço em branco para evitar conflitos
                map[row][col] = ' ';

                (*enemy_count)++;
            }
        }
    }
}

void draw_enemies(Enemy enemies[MAX_ENEMIES], int enemy_count)
{
    for (int i = 0; i < enemy_count; i++)
        DrawRectangle(enemies[i].col * TILE_SIZE, enemies[i].row * TILE_SIZE, TILE_SIZE, TILE_SIZE, ORANGE);
}