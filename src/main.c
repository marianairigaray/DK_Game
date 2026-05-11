#include "map.h"
#include <stdio.h>

int main()
{
	char map[MAP_ROWS][MAP_COLS];
	read_map(map, 1);

	for(int i = 0; i < 30; i++)
    {
        for(int j = 0; j < 30; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }

	return 0;
}