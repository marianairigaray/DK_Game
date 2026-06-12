#ifndef MENU_H
#define MENU_H

#include "game_state.h"

#define NUM_BUTTONS 4 // Numero de botões

typedef enum
{
    MAIN_MENU,
    RANKING
} Menu_state;

typedef enum 
{
    NO_OPTION = -1,
    MENU_CONTINUE,
    MENU_NEW_GAME,    
    MENU_RANKING,
    MENU_EXIT
} Menu_options;

void menu_init(bool active_game);
void draw_menu();
void reset_button_selector();
Game_state menu(Menu_options menu_option, Menu_state *menu_state);
Menu_options read_option(bool active_game); // APAGAR
Menu_options update_menu(bool active_game);

#endif