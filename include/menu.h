#ifndef MENU_H
#define MENU_H

typedef enum 
{
    NEW_GAME,
    CONTINUE,
    RANKING,
    EXIT
} Menu_options;

void draw_menu();
void menu(Menu_options menu);
Menu_options read_option();

#endif