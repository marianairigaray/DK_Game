#include "collision.h"
#include "player.h"

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