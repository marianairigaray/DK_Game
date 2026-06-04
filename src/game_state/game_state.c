#include "game_state.h"
#include "raylib.h"
#include "map.h"
#include "player.h"
#include "points.h"
#include "save.h"
#include "enemy.h"
#include <stdbool.h>

void reset_game(char map[MAP_ROWS][MAP_COLS], int current_level, Player *player, Enemy enemies[MAX_ENEMIES], int *enemy_count)
{
    // reseta mapa
    read_map(map, current_level);

    // reseta vidas do player
    save_game_lives(DEFAULT_LIVES);

    // reseta os pontos do player
    save_score(0);

    // reseta player
    *player = create_player(map);

    // reseta inimigos
    *enemy_count = 0;
    create_enemies(enemies, map, enemy_count);
}

void load_level(int level_num, char map[MAP_ROWS][MAP_COLS], Player *player, Enemy enemies[MAX_ENEMIES], int *enemy_count, bool keep_lives) 
{
    // 1. Guarda as vidas atuais do jogador antes de o recriar
    int current_lives = player->lives;

    // 2. Limpa a matriz do mapa antigo preenchendo-a com espaços vazios
    for (int r = 0; r < MAP_ROWS; r++) {
        for (int c = 0; c < MAP_COLS; c++) {
            map[r][c] = ' ';
        }
    }

    // 3. Lê o ficheiro do novo mapa (assets/maps/map0.txt, map1.txt, etc.)
    read_map(map, level_num);
    
    // 4. Recria o jogador na nova posição de spawn encontrada no mapa
    *player = create_player(map);
    
    // 5. Se mudaste de fase (keep_lives == true), devolve as vidas antigas ao jogador
    if (keep_lives) {
        player->lives = current_lives;
    }

    // 6. Zera o contador de inimigos e cria os novos inimigos desta fase
    *enemy_count = 0;
    create_enemies(enemies, map, enemy_count);
}

void game_over(Game_state *game_state)
{
     
    // caso top 10 -> perguntar nome e salvar placar

    // mostrar o placar

    // voltar para o menu (caso o usuario digite ou pressione alguma tecla)
    if (IsKeyDown(KEY_SPACE)) *game_state = MENU;
}

void draw_game_over()
{
    DrawText("GAME_OVER", 10, 10, 40, BLACK);
    DrawText("Pressione [SPACE] para voltar ao menu", 10, 60, 15, BLACK);
}