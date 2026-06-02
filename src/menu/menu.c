#include "menu.h"
#include "raylib.h"
#include "game_state.h"

#define NUM_BUTTONS 4 // Numero de botões
#define BUTTON_WIDTH 200 // Largura do botão
#define BUTTON_HEIGHT 50 // Largura do botão
#define PADDING 10 // Espaço entre os botões

static Rectangle buttons[NUM_BUTTONS] = { 100, 150, BUTTON_WIDTH, BUTTON_HEIGHT };

void menu_init()
{
    // Define a posição e o tamanho dos botões do menu
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        buttons[i].x = 100;
        buttons[i].y = 150 + (i * (BUTTON_HEIGHT + PADDING));
        buttons[i].width = BUTTON_WIDTH;
        buttons[i].height = BUTTON_HEIGHT;
    }
}

Menu_options read_option()
{
    Vector2 mouse_positon = GetMousePosition();

    if (CheckCollisionPointRec(mouse_positon, buttons[NEW_GAME]))
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return NEW_GAME;
        }
    }

    if (CheckCollisionPointRec(mouse_positon, buttons[CONTINUE]))
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return CONTINUE;
        }
    }

    if (CheckCollisionPointRec(mouse_positon, buttons[RANKING]))
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return RANKING;
        }
    }

    if (CheckCollisionPointRec(mouse_positon, buttons[EXIT]))
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return EXIT;
        }
    }

    return NO_OPTION;
}

Game_state menu(Menu_options menu_option)
{
    switch (menu_option)
    {
        case NEW_GAME:

            return PLAYING;
        break;
        case CONTINUE:

            return PLAYING;
        break;
        case RANKING:

        break;
        case EXIT:

            return GAME_EXIT;
        break;
        default:

            return MENU;
        break;
    }
}

void draw_menu()
{
    DrawText("DONKEY KONG", 10, 10, 40, BLACK);

    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        DrawRectangleRec(buttons[i], RED);
    }

    DrawText("NEW GAME", 100, 150, 20, BLACK);
    DrawText("CONTINUE GAME", 100, 210, 20, BLACK);
    DrawText("RANK", 100, 270, 20, BLACK);
    DrawText("EXIT", 100, 330, 20, BLACK);
    
}