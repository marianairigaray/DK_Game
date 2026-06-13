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
#include "ranking.h"
#include "save.h"
#include "pause_menu.h"

#define NUM_LEVELS 3

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DK Game");

    SetTargetFPS(60);

    // Initialize all required variables and load all required data

    bool exit_game = false;
    SetExitKey(KEY_NULL);

    // Inicializa a semente para geração de números aleatórios
    srand(time(NULL));

    Game_state game_state = MENU;
    Menu_state menu_state = MAIN_MENU;
    Menu_options menu_option = NO_OPTION;
    bool active_game = has_active_game();
    menu_init(active_game);
    pause_menu_init();

    End_game_states end_game_state = GAME_OVER_SCREEN;

    Ranking ranking[MAX_RANKING_ENTRIES] = {0};
    Ranking ranked_player = {0};
    int ranked_players = 0;

    int current_level = 0; // Começa no nível 0 (map0.txt)

    char map[MAP_ROWS][MAP_COLS] = {0};

    read_map(map, current_level);

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
    while (!exit_game && !WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------

        switch (game_state)
        {
            case MENU:

                switch (menu_state)
                {
                    case MAIN_MENU:
                        active_game = has_active_game();
                        menu_option = update_menu(active_game);
                        game_state = menu(menu_option, &menu_state);
                    break;
                
                    case RANKING:

                        ranked_players = load_ranking(ranking);

                        if (is_return_main_menu())
                        {
                            menu_state = MAIN_MENU;
                        }
                    break;
                }

            break;

            case NEW_GAME:

                reset_game(map, &player, enemies, &enemy_count);

                game_state = PLAYING;

            break;

            case PLAYING:

                update_player(&player, map);
                move_enemies(map, enemies, enemy_count);
                check_player_enemy_collisions(&player, enemies, enemy_count, map);
                update_points(map, &player);

                if (check_level_complete(player, map))
                {
                    current_level++; // Avança o número do nível
                    
                    if (current_level >= NUM_LEVELS) 
                    {
                        current_level = 0; // reseta para o primeiro level
                        player.points += 1000; // Player ganha 1000 pontos por ter vencido o jogo
                        end_game_state = VICTORY_SCREEN;
                        game_state = END_GAME;
                    }
                    else
                    {
                        // Carrega o novo mapa limpando o antigo e mantendo as vidas atuais (true)
                        load_level(current_level, map, &player, enemies, &enemy_count, true);
                    
                        printf("Nivel %d carregado com sucesso!\n", current_level);
                    }
                }

                if (!player.is_active)
                {
                    game_state = END_GAME;
                }

                if (is_pause_pressed()) 
                {
                    game_state = PAUSED;
                }
                // ------------------------------------

            break;

            case PAUSED:

                Pause_options pause_option = read_pause_menu();
                game_state = pause_to_game_state(pause_option);

            break;

            case END_GAME:
                
                switch(end_game_state)
                {
                    case VICTORY_SCREEN:
                    case GAME_OVER_SCREEN:

                        end_game(&end_game_state, ranking, &ranked_players, player.points);

                    break;

                    case INPUT_NAME:

                        if (update_ranking(ranking, &ranked_player, &ranked_players, player.points)) 
                        {
                            for (int i = 0; i < ranked_player.name_len; i++)
                                ranked_player.name[i] = '\0';

                            ranked_player.name_len = 0;

                            end_game_state = VIEW_RANKING;
                        }

                    break;

                    case VIEW_RANKING:

                        if (is_return_main_menu())
                        {
                            end_game_state = GAME_OVER_SCREEN;
                            game_state = MENU;
                            reset_button_selector();
                        }

                    break;
                }

            break;

            case EXIT:

                exit_game = true;

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

                switch (menu_state)
                {
                    case MAIN_MENU:

                        draw_menu();

                    break;
                
                    case RANKING:

                        draw_ranking(ranking, ranked_players);

                    break;
                }

                
            break;
            case PLAYING:

                draw_map(map);
                draw_player(player);
                draw_enemies(enemies, enemy_count);

                DrawText(TextFormat("Lives: %d", player.lives), 10, 10, 20, BLACK);

                DrawText(TextFormat("Level: %d", current_level), 210, 10, 20, BLACK);

                draw_points(&player);

            break;
            
            case PAUSED:

                draw_menu_pause();

            break;
            
            case END_GAME:
                
                switch(end_game_state)
                {
                    case VICTORY_SCREEN:

                        draw_victory();
                    
                    break;

                    case GAME_OVER_SCREEN:

                        draw_game_over();

                    break;

                    case INPUT_NAME:

                        draw_input_name_screen(ranked_player);

                    break;

                    case VIEW_RANKING:

                        draw_ranking(ranking, ranked_players);

                    break;
                }

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