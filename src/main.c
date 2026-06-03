#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "enemy.h"
#include "game_state.h"
#include "map.h"
#include "menu.h"
#include "player.h"
#include "points.h"
#include "collision.h"
#include "save.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DK Game");

    SetTargetFPS(60);

    // Initialize all required variables and load all required data

    // Inicializa a semente para geração de números aleatórios
    srand(time(NULL));

    Game_state game_state = MENU;
    Menu_state menu_state = MAIN_MENU;
    Menu_options menu_option = NO_OPTION;
    menu_init();

    int current_level = 0; // Começa no nível 0 (map0.txt)

    char map[MAP_ROWS][MAP_COLS] = {0};

    read_map(map, 0);

    Player player = create_player(map);

    // Creates enemies array
    Enemy enemies[MAX_ENEMIES] = {0};
    int enemy_count = 0;
    create_enemies(enemies, map, &enemy_count);

    // Debug information
    printf("Player row = %d, col = %d\n", player.row, player.col);
    for (int i = 0; i < enemy_count; i++)
    {
        printf("Enemy %d x = %f, y = %f\n", i+1, enemies[i].x, enemies[i].y);
        printf("Direction = %d\n", enemies[i].direction);
    }
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------

        switch (game_state)
        {
            case MENU:

                switch (menu_state)
                {
                    case MAIN_MENU:
                        menu_option = read_option();
                        game_state = menu(menu_option);
                    break;
                
                    default:
                        break;
                }

            break;

            case PLAYING:

                update_player(&player, map);
                move_enemies(map, enemies, enemy_count);
                check_player_enemy_collisions(&player, enemies, enemy_count, map);
                update_points(map, &player);

                if (check_level_complete(player, map))
                {
                    current_level++; // Avança o número do nível
                    
                    
                    if (current_level > 1) 
                    {
                        current_level = 0; // Reinicia no mapa 0 (ou mude para game_state = MENU se preferir acabar o jogo)
                    }
                    
                    // Carrega o novo mapa limpando o antigo e mantendo as vidas atuais (true)
                    load_level(current_level, map, &player, enemies, &enemy_count, true);
                    
                    printf("Nivel %d carregado com sucesso!\n", current_level);
                }
                // ------------------------------------

                break;

            case PAUSED:
            break;

            case GAME_OVER:
            break;

            case GAME_EXIT:
            break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (game_state)
        {
            case MENU:

                draw_menu();
            
                break;
            case PLAYING:

                draw_map(map);
                draw_player(player);
                draw_enemies(enemies, enemy_count);

                DrawText(TextFormat("Lives: %d", player.lives), 10, 10, 20, BLACK);

                draw_points(&player);

            break;
        }
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}