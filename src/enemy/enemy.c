#include "enemy.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "map.h"

// Problemas para resolver:
// 3º - Velocidade dos inimigos (eles estão muito rápidos)

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
                enemies[*enemy_count].row = row;
                enemies[*enemy_count].col = col;

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
        DrawRectangle(enemies[i].col * TILE_SIZE, enemies[i].row * TILE_SIZE, TILE_SIZE, TILE_SIZE, ORANGE);
}

// Verifica se o próximo movimento do inimigo é válido
static bool is_valid_move(char map[MAP_ROWS][MAP_COLS], int row, int col)
{
    // Caso ultrapasse a borda horizontal esquerda
    if (col >= MAP_COLS)
        return false;

    // Caso ultrapasse a borda horizontal direita
    if (col < 0)
        return false;

    // Caso não exista chão embaixo
    if (map[row + 1][col] == ' ')
        return false;

    return true;
}

void move_enemies(char map[MAP_ROWS][MAP_COLS], Enemy enemies[MAX_ENEMIES], int enemy_count)
{
    for (int i = 0; i < enemy_count; i++)
    {

        int new_col = enemies[i].col + enemies[i].direction;

        if (is_valid_move(map, enemies[i].row, new_col))
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