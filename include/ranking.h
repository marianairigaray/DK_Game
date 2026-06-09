#ifndef RANKING_H
#define RANKING_H

#include <stdbool.h>

#define NAME_SIZE 20
#define MAX_RANKING_ENTRIES 10 // Máximo de jogadores no placar

typedef struct Ranking
{
    char name[NAME_SIZE];
    int name_len; // tamanho real do nome do player (contando com o \0)
    int score;
} Ranking;

bool is_ranked(Ranking ranking[MAX_RANKING_ENTRIES], int *ranked_players, int score);
bool update_ranking(Ranking ranking[MAX_RANKING_ENTRIES], Ranking *ranked_player, int *ranked_players, int score);
bool is_return_main_menu();
void draw_input_name_screen(Ranking ranked_player);
void draw_ranking();

#endif