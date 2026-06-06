#ifndef MENU_H
#define MENU_H

#include "game_state.h"

#define NUM_BUTTONS 4 // Numero de botões
#define BUTTON_WIDTH 200 // Largura do botão
#define BUTTON_HEIGHT 50 // Largura do botão
#define PADDING 10 // Espaço entre os botões

typedef enum
{
    MAIN_MENU,
    RANKING
} Menu_state;

typedef enum 
{
    MENU_NEW_GAME,    
    MENU_CONTINUE,
    MENU_RANKING,
    MENU_EXIT,
    NO_OPTION
} Menu_options;

void menu_init();
void draw_menu();
Game_state menu(Menu_options menu_option, Menu_state *menu_state);
Menu_options read_option();

#endif