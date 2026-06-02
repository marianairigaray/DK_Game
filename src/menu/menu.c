#include "menu.h"
#include "raylib.h"

#define BUTTON_WIDTH 200 // Largura do botão
#define BUTTON_HEIGHT 50 // Largura do botão

static Rectangle button = { 100, 150, BUTTON_WIDTH, BUTTON_HEIGHT };

void menu_init()
{
    
}

Menu_options read_option()
{
    Vector2 mouse_positon = GetMousePosition();

    if (CheckCollisionPointRec(mouse_positon, button))
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return CONTINUE;
        }
    }
}

void menu(Menu_options menu)
{
    switch (menu)
    {
        case NEW_GAME:
            /* code */
            break;
        case CONTINUE:

            break;
        case RANKING:
            break;
        case EXIT:
            break;
        default:
            break;
    }
}

void draw_menu()
{
    DrawText("DONKEY KONG", 10, 10, 40, BLACK);

    DrawRectangleRec(button, RED);
    DrawText("CONTINUE GAME", 100, 150, 20, BLACK);
    DrawText("(click here)", 100, 170, 10, BLACK); 
}