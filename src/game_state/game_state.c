#include "game_state.h"
#include "raylib.h"
#include "map.h"
#include "player.h"
#include "points.h"
#include "save.h"
#include "enemy.h"
#include "ranking.h"
#include <stdio.h>
#include <stdbool.h>

bool has_active_game() {

    char file_name[] = "./data/save.bin";

    // verificar se o arquivo existe
    if (!FileExists(file_name))
    {
        // se não existir vai direto para o menu
       return false;
    }

    // se existir -> vai verificar se existe jogo salvo ou não
    FILE *save = fopen(file_name, "rb");
    if (save == NULL)
    {
        printf("Could not open %s to read.\n", file_name);
        return false;
    }

    bool active_game;

    fread(&active_game, sizeof(bool), 1, save);

    fclose(save);

    return active_game;
}

static void save_active_game(bool active_game) {

    FILE *file = fopen("./data/save.bin", "wb");
    if (file == NULL)
    {
        printf("Could not open save.bin to write.\n");
        return;
    }

    fwrite(&active_game, sizeof(bool), 1, file);

    fclose(file);
}

void reset_game(char map[MAP_ROWS][MAP_COLS], Player *player, Enemy enemies[MAX_ENEMIES], int *enemy_count)
{
    // inicia novo save
    save_active_game(true);

    // reseta mapa
    read_map(map, 0);

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

bool is_pause_pressed() {
    
    if (IsKeyPressed(KEY_TAB) || IsKeyPressed(KEY_ESCAPE)) return true;
    
    return false;
} 

void end_game(End_game_states *end_game_state, Ranking ranking[MAX_RANKING_ENTRIES], int *ranked_players, int score)
{
    save_active_game(false);

    // Se o usuário apertar no espaço, ele vai para a tela de rankig ou de inserir o nome no rankig (depende da pontuação)
    if (IsKeyPressed(KEY_SPACE))
    {
        if (is_ranked(ranking, ranked_players, score))
        {
            *end_game_state = INPUT_NAME;
        }
        else
        {
            *end_game_state = VIEW_RANKING;
        }
    } 
}

void draw_victory()
{
    DrawText("VICTORY", 10, 10, 40, BLACK);
    DrawText("Press [SPACE] to continue", 10, 60, 15, BLACK);
}

void draw_game_over()
{
    DrawText("GAME_OVER", 10, 10, 40, BLACK);
    DrawText("Press [SPACE] to continue", 10, 60, 15, BLACK);
}