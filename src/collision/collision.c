#include "collision.h"
#include "player.h"
#include "map.h"

#include "raylib.h"
#include <stdio.h>

void check_player_enemy_collisions(Player *player, Enemy enemies[MAX_ENEMIES], int enemy_count, char map[MAP_ROWS][MAP_COLS])
{
    // 1. Cria o retângulo de colisão do jogador
    Rectangle playerRec = { player->x, player->y, player->width, player->height };

    // 2. Passa por todos os inimigos do mapa
    for (int i = 0; i < enemy_count; i++)
    {
        Rectangle enemyRec = { enemies[i].x, enemies[i].y, TILE_SIZE, TILE_SIZE };

        // 3. Verifica se houve impacto
        if (CheckCollisionRecs(playerRec, enemyRec))
        {
            player->lives--;
            save_game_lives(player->lives); // Salva no arquivo save.txt

            if (player->lives <= 0) 
            {
                printf("GAME OVER!\n");
                save_game_lives(3); // Reseta o save para 3 vidas
                
                // Reinicia o jogador do zero usando a função existente
                *player = create_player(map); 
            }
            else 
            {
                // Se não deu Game Over, apenas joga o player para o início do mapa
                player->x = player->spawn_x; 
                player->y = player->spawn_y; 
                
            }
            
            break; // Para o laço para evitar checar múltiplas colisões no mesmo frame
        }
    }
}
bool check_level_complete(Player player, char map[MAP_ROWS][MAP_COLS])
{
    // Converte a posição do jogador de pixels para coordenadas da matriz (Grid)
    int left_col   = (int)(player.x) / TILE_SIZE;
    int right_col  = (int)(player.x + player.width - 1) / TILE_SIZE;
    int top_row    = (int)(player.y) / TILE_SIZE;
    int bottom_row = (int)(player.y + player.height - 1) / TILE_SIZE;

    // Garante que não vamos ler índices fora dos limites da matriz do mapa
    if (left_col < 0) left_col = 0;
    if (right_col >= MAP_COLS) right_col = MAP_COLS - 1;
    if (top_row < 0) top_row = 0;
    if (bottom_row >= MAP_ROWS) bottom_row = MAP_ROWS - 1;

    // Percorre todas as células do mapa que o retângulo do jogador está a ocupar
    for (int r = top_row; r <= bottom_row; r++)
    {
        for (int c = left_col; c <= right_col; c++)
        {
            // Se encontrar a letra 'F', significa que o jogador chegou ao fim da fase
            if (map[r][c] == 'F')
            {
                return true;
            }
        }
    }

    return false;
}