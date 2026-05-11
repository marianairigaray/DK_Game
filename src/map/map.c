#include <stdio.h>
#include "map.h"

/* Opens and reads a map from a file from the assets/maps directory */
void read_map(int num_map)
{
    char file_name[30];

    sprintf(file_name, "./assets/maps/map%d.txt", num_map);
    
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", file_name);
        return;
    }

    char map[900]; 

    while(fread(&map, sizeof(char), 900, file))
    {
        
    }

    for(int i = 0; i < 900; i++)
    {
        printf("%c", map[i]);
    }

    printf("Map read successfully.\n");

}