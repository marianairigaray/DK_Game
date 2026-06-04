#ifndef SAVE_H
#define SAVE_H

#define DEFAULT_LIVES 3

// Salva a quantidade de vidas atual no arquivo save.txt
void save_game_lives(int lives);

// Carrega as vidas salvas. Se o arquivo não existir, retorna o valor padrão
int load_game_lives(int default_lives);

#endif