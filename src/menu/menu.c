#include "menu.h"
#include "raylib.h"
#include "game_state.h"
#include "button.h"

static Rectangle buttons[NUM_BUTTONS] = { 0 };
static int button_selector = 0;
static bool button_hoover[NUM_BUTTONS] = { false };

void menu_init(bool active_game)
{
    // Define a posição e o tamanho dos botões do menu
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        buttons[i].x = 100;
        buttons[i].y = 150 + (i * (BUTTON_HEIGHT + PADDING));
        buttons[i].width = BUTTON_WIDTH;
        buttons[i].height = BUTTON_HEIGHT;
    }

    // Define o index do botão em seleção
    button_selector = active_game ? 0 : 1;
}

Menu_options update_menu(bool active_game)
{
    // Reseta o hoover
    for (int i = 0; i < NUM_BUTTONS; i++)
        button_hoover[i] = false;

    int old_button_selector = button_selector;

    // SELEÇÃO DO MENU POR MOUSE

    int button_selected = read_mouse(buttons, NUM_BUTTONS, &button_selector);

    // Caso selecionada a opção de CONTINUAR mas não tem jogo salvo,
    if ((!active_game) && (button_selector == MENU_CONTINUE))
    {
        // Cancela o clique
        button_selected = NO_OPTION;

        // Ignora o movimento do mouse e mantém o foco antigo
        button_selector = old_button_selector;
    }

    // Se o mouse clicou em um botão válido, ativa o hoover e retorna o botão selecionado
    if (button_selected != NO_OPTION) 
    {
        if (button_selected == NEW_GAME) button_selector = MENU_CONTINUE; // Caso o player volte para o menu no meio do jogo, o botão em foco sera o de CONTINUE

        button_hoover[button_selected] = true;
        return button_selected;
    }

    // SELEÇÃO DO MENU POR TECLADO

    button_selected = read_keyboard(NUM_BUTTONS, &button_selector);

    // Caso selecionada a opção de CONTINUAR mas não tem jogo salvo,
    if ((!active_game) && (button_selector == MENU_CONTINUE))
    {
        // Cancela a seleção
        button_selected = NO_OPTION;

        // Se estava no último botão e subiu, pula o CONTINUE e vai para o NEW GAME (1)
        if (old_button_selector == NUM_BUTTONS-1) button_selector = 1;

        // Se estava no NEW GAME (1) e subiu, pula o CONTINUE e vai para o último botão
        if (old_button_selector == 1) button_selector = NUM_BUTTONS-1;
    }

    // Da hoover no botão em foco
    button_hoover[button_selector] = true;

    if (button_selected == NEW_GAME) button_selector = MENU_CONTINUE; // Caso o player volte para o menu no meio do jogo, o botão em foco sera o de CONTINUE

    return button_selected;
}

Game_state menu(Menu_options menu_option, Menu_state *menu_state)
{
    switch (menu_option)
    {
        case MENU_CONTINUE:
            return PLAYING;

        case MENU_NEW_GAME:
            return NEW_GAME;
        
        case MENU_RANKING:
            *menu_state = RANKING;
            return MENU;

        case MENU_EXIT:
            return EXIT;

        default:
            return MENU;
    }
}

void reset_button_selector() {
    button_selector = NEW_GAME;
}

void draw_menu()
{
    DrawText("DONKEY KONG", 10, 10, 40, BLACK);

    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        DrawRectangleRec(buttons[i], button_hoover[i] ? RED : GRAY);
    }

    DrawText("CONTINUE GAME", 100, 150, 20, BLACK);
    DrawText("NEW GAME", 100, 210, 20, BLACK);
    DrawText("RANKING", 100, 270, 20, BLACK);
    DrawText("EXIT", 100, 330, 20, BLACK);
}