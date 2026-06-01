#include "save.h"
#include <stdio.h>

//salva a quantidade de vidas atual no arquivo save.txt
void save_game_lives(int lives)
{
    FILE *file = fopen("save.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo de save para escrita!\n");
        return;
    }

    fprintf(file, "%d", lives);
    fclose(file);
    printf("Jogo salvo! Vidas guardadas: %d\n", lives);
}

//carrega as vidas salvas. Se o arquivo não existir, retorna o valor padrão
int load_game_lives(int default_lives)
{
    FILE *file = fopen("save.txt", "r");
    if (file == NULL)
    {
        return default_lives; // Se o arquivo não existir, começa com o padrão (primeira vez jogando)
    }
    // Tenta ler o número de vidas do arquivo. Se falhar, retorna o padrão
    int lives;
    if (fscanf(file, "%d", &lives) != 1)
    {
        lives = default_lives; // Se o arquivo estiver corrompido, usa o padrão
    }

    fclose(file);
    return lives;
}