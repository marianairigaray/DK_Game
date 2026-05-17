#include "enemy.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "map.h"

// Problemas para resolver:
// 1º - Uso de enum é necessário?
// 2º - A verificação não usa a função collision (voltamos ela para personagem ou modificamos para ela ser mais genérica?)
// 3º - Velocidade dos inimigos (eles estão muito rápidos)

void create_enemies(Enemy enemies[MAX_ENEMIES], char map[MAP_ROWS][MAP_COLS], int *enemy_count)
{
    // Inicializa a semente para geração de números aleatórios
    srand(time(NULL));

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

                // Guarda a posição inicial do inimigo atual 
                enemies[*enemy_count].row = row;
                enemies[*enemy_count].col = col;

                // Retira a letra 'E' do mapa e substituí por espaço em branco para evitar conflitos
                map[row][col] = ' ';

                // Inicializa a direção de movimento do inimigo aleatóriamente
                enemies[*enemy_count].direction = 0 + (rand() % (1 - 0 + 1));
                
                // Caso a direção seja 0, ela é substituida por -1 (movimentação para esquerda)
                if (enemies[*enemy_count].direction == 0)
                    enemies[*enemy_count].direction = -1;

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

void move_enemies(Enemy enemies[MAX_ENEMIES], int enemy_count)
{
    for (int i = 0; i < enemy_count; i++)
    {

        int new_col = enemies[i].col + enemies[i].direction;

        if ((new_col < MAP_COLS) && (new_col >= 0))
        {
            enemies[i].col = new_col;
        }
        else
        {
            enemies[i].direction *= -1; // Toggle na direção
            enemies[i].col = enemies[i].col + enemies[i].direction;
        }
            
    }
}