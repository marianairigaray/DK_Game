#ifndef MENU_H
#define MENU_H

#include "game_state.h"

typedef enum
{
    MAIN_MENU,
    RANK
} Menu_state;

typedef enum 
{
    NEW_GAME,
    CONTINUE,
    RANKING,
    EXIT
} Menu_options;

void draw_menu();
Game_state menu(Menu_options menu_option);
Menu_options read_option();

#endif