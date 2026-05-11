#include <stdio.h>
#include "map.h"
#include "raylib.h"

/* Opens and reads a map from a file from the assets/maps directory */
void read_map(char map[MAP_ROWS][MAP_COLS], int num_map)
{
    char file_name[50];

    sprintf(file_name, "./assets/maps/map%d.txt", num_map);
    
    FILE *file = fopen(file_name, "rb");
    if (file == NULL)
    {
        printf("Could not open %s.\n", file_name);
        return;
    }
 
    char c;
    int row = 0, col = 0;

    // Read the file character by character, ignoring newlines (\n) and carriage returns (\r)
    while(fread(&c, sizeof(char), 1, file) && row < MAP_ROWS)
    {
        if(!(c == '\n' || c == '\r'))
        {
            map[row][col] = c;
            
            col++;
            
            if(col == MAP_COLS)
            {
                row++;
                col = 0;
            }
        }
    }

    fclose(file);

}
void draw_map(char map[MAP_ROWS][MAP_COLS])//Desenha o mapa na tela usando a função DrawRectangle da Raylib
{
    for(int i = 0; i < MAP_ROWS; i++)
    {
        for(int j = 0; j < MAP_COLS; j++)
        {
            char c = map[i][j];// Obtém o caractere da posição atual do mapa
            if(c == 'Z')// Se o caractere for 'Z', desenha um retângulo preto representando uma parede
            {
                DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLACK);
            }
            else if(c == 'P')// Se o caractere for 'P', desenha um retângulo vermelho representando o jogador
            {
                DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED);
            }else if(c == 'D')// Se o caractere for 'D', desenha um retângulo laranja representando o Donkey Kong
            {
                DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, ORANGE);
            }
        }
    }
}