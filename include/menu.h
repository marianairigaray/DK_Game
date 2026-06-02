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
    EXIT,
    NO_OPTION
} Menu_options;

void menu_init();
void draw_menu();
Game_state menu(Menu_options menu_option);
Menu_options read_option();

#endif