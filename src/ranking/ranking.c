#include "ranking.h"

#include "raylib.h"

#include <stdio.h>
#include <stdbool.h>

#include "menu.h"

// Carrega o ranking e salva no array de structs Ranking
// Essa função recebe um ranking zerado, caso o arquivo não exista, ela retorna o ranking zerado
// caso o arquivo exista, ela retorna o ranking com as informações salvas do arquivo
static int load_ranking(Ranking ranking[MAX_RANKING_ENTRIES])
{
    // Zera o ranking recebido
    for (int i = 0; i < MAX_RANKING_ENTRIES; i++)
    {
        ranking[i] = (Ranking){0};
    }

    char file_name[] = "./data/ranking.bin";

    FILE *file = fopen(file_name, "rb");
    if (file == NULL)
    {
        printf("Could not open %s to read.\n", file_name);
        return 0;
    }

    int entries_read = fread(ranking, sizeof(Ranking), MAX_RANKING_ENTRIES, file);
    
    fclose(file);

    return entries_read;
}

// Salva o ranking no arquivo
static void save_ranking(Ranking ranking[MAX_RANKING_ENTRIES], const int ranked_players)
{
    char file_name[] = "./data/ranking.bin";

    FILE *file = fopen(file_name, "wb");
    if (file == NULL)
    {
        printf("Could not open %s to write.\n", file_name);
        return;
    }

    fwrite(ranking, sizeof(Ranking), ranked_players, file);

    fclose(file);
}

static void insert_in_ranking(Ranking ranking[MAX_RANKING_ENTRIES], Ranking *ranked_player, const int ranked_players)
{
    // 
    int index_insertion;

    Ranking old_rankig, aux;

    bool is_position_foud = false;

    for (int i = 0; i < ranked_players; i++)
    {
        // veri
        if (is_position_foud == false)
        {
            if (ranking[i].score < ranked_player->score)
            {
                index_insertion = i;
                old_rankig = ranking[i];
                ranking[i] = *ranked_player; // insere o player na posição correta no ranking
                is_position_foud = true;
            }
        }
        else
        {
            aux = ranking[i];
            ranking[i] = old_rankig;
            old_rankig = aux;
        }
    }

    for (int i = 0; i < ranked_players; i++)
    {
        printf("Ranked player %d = name: %s, score: %d\n", i, ranking[i].name, ranking[i].score);
    }

    save_ranking(ranking, ranked_players);
}

static int get_name(Ranking *ranked_player)
{
    char c = GetCharPressed();

    if ((c != 0) && (ranked_player->name_len < NAME_SIZE-1))
    {
        ranked_player->name[ranked_player->name_len] = c;
        ranked_player->name_len++;
        ranked_player->name[ranked_player->name_len] = '\0';
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        ranked_player->name[ranked_player->name_len] = '\0';
        return 0; // acabou de ler o nome
    }

    if ((IsKeyPressed(KEY_BACKSPACE)) && (ranked_player->name_len > 0))
    {
        ranked_player->name_len--;
        ranked_player->name[ranked_player->name_len] = '\0';
    }

    return 1; // ainda faltam caracteres
}

bool is_ranked(Ranking ranking[MAX_RANKING_ENTRIES], int *ranked_players, int score) 
{
    // Carrega o ranking salvo; load_ranking retorna o numero de ranked players lido
    *ranked_players = load_ranking(ranking);

    if (score > ranking[MAX_RANKING_ENTRIES-1].score)
        return true;

    return false;
}

bool update_ranking(Ranking ranking[MAX_RANKING_ENTRIES], Ranking *ranked_player, int *ranked_players, int score)
{
    // Lê o nome do player
    if (get_name(ranked_player))
    {
        return false; // nome ainda esta sendo digitado (demora varios frames para ser completamente digitado)
    }

    // Salva a score do player
    ranked_player->score = score;

    // Incrementa o contador de playes no ranking
    if (*ranked_players < MAX_RANKING_ENTRIES) (*ranked_players)++; // deposito todo meu odio ao c nessa linha

    insert_in_ranking(ranking, ranked_player, *ranked_players);

    return true;
}

bool is_return_main_menu()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        return true;
    }

    return false;
}

void draw_ranking() 
{
    DrawText("RANKING", 10, 10, 40, BLACK);
    DrawRectangle(50, 500, BUTTON_WIDTH, BUTTON_HEIGHT, RED);
    DrawText("RETURN", 50, 500, 20, BLACK);
}

void draw_input_name_screen(Ranking ranked_player)
{
    DrawText("Name: ", 120, 150, 20, BLACK);
    DrawText(TextFormat("%s", ranked_player.name), 190, 150, 20, BLACK);
    
    // Esse calculo é para dar toggle no cursor de digitação
    if (((int) (GetTime() * 2) % 2) == 0) 
    {
        DrawText("|", 190 + MeasureText(ranked_player.name, 20), 150, 20, BLACK);
    }
}