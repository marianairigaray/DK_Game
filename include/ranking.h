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

void update_ranking(int score, Ranking *ranked_player);
bool is_return_main_menu();
void draw_input_name_screen(Ranking ranked_player);
void draw_ranking();

#endif