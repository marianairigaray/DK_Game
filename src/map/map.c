#include <stdio.h>
#include "map.h"

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