#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "game_state.h"

typedef enum Pause_options
{
    PAUSE = -1,
    PAUSE_CONTINUE_GAME,
    PAUSE_RETURN_TO_MENU,
    PAUSE_EXIT_GAME
} Pause_options;

void pause_menu_init();
Pause_options read_pause_menu();
Game_state pause_to_game_state(Pause_options pause_option);
void draw_menu_pause();

#endif