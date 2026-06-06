#include "menu.h"
#include "raylib.h"
#include "game_state.h"

static Rectangle buttons[NUM_BUTTONS] = { 0 };
static unsigned int button_selector = 0;
static bool button_hoover[NUM_BUTTONS] = { false };

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

    // Reseta o hoover
    for (int i = 0; i < NUM_BUTTONS; i++)
        button_hoover[i] = false;

    // SELEÇÃO DO MENU POR MOUSE

    // Verifica se houve colisão do mouse com cada um dos NUM_BUTTONS botões
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        if (CheckCollisionPointRec(mouse_positon, buttons[i]))
        {
            button_selector = i;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                return button_selector;
            }
        }
    }

    // SELEÇÃO DO MENU POR TECLADO

    if (IsKeyPressed(KEY_UP))
    {
        // Se o botão atualmente em foco não for o primeiro
        if (button_selector > 0)
        {
            // Move o foco para o botão anterior (subir no menu)
            button_selector--;
        }
        else
        {
            // Efeito "Loop": Se estiver no topo (primeiro botão), move o foco para o último botão
            button_selector = NUM_BUTTONS - 1;
        }
    }

    if (IsKeyPressed(KEY_DOWN))
    {
        // Se o botão atualmente em foco não for o último
        if (button_selector < NUM_BUTTONS - 1)
        {
            // Move o foco para o próximo botão (descer no menu)
            button_selector++;
        }
        else
        {
            // Efeito "Loop": Se estiver no último botão, move o foco para o primeiro botão
            button_selector = 0;
        }
    }

    // Da hoover no botão em foco
    button_hoover[button_selector] = true;

    // Seleciona a opção do menu equivalente ao "index" do botão selecionado (as opções do menu são um enum)
    if (IsKeyPressed(KEY_ENTER))
    {
        return button_selector;
    }

    return NO_OPTION;
}

Game_state menu(Menu_options menu_option, Menu_state *menu_state)
{
    switch (menu_option)
    {
        case MENU_NEW_GAME:

            return NEW_GAME;
        break;
        case MENU_CONTINUE:

            return PLAYING;
        break;
        case MENU_RANKING:

            *menu_state = RANKING;
            return MENU;
        break;
        case MENU_EXIT:

            return EXIT;
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
        DrawRectangleRec(buttons[i], button_hoover[i] ? RED : GRAY);
    }

    DrawText("NEW GAME", 100, 150, 20, BLACK);
    DrawText("CONTINUE GAME", 100, 210, 20, BLACK);
    DrawText("RANKING", 100, 270, 20, BLACK);
    DrawText("EXIT", 100, 330, 20, BLACK);
}