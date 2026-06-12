#include "pause_menu.h"
#include "raylib.h"
#include "button.h"
#include "game_state.h"

#define NUM_BUTTONS 3
#define NO_OPTION -1

static Rectangle buttons[NUM_BUTTONS] = { 0 };
static unsigned int button_selector = 0;
static bool button_hoover[NUM_BUTTONS] = { false };

void pause_menu_init()
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

static void reset_button_selector()
{
    button_selector = PAUSE_CONTINUE_GAME;
}

Pause_options read_pause_menu()
{
    // Reseta o hoover
    for (int i = 0; i < NUM_BUTTONS; i++)
        button_hoover[i] = false;
    
    int button_selected;
    
    // SELEÇÃO DO MENU DE PAUSA POR MOUSE
    button_selected = read_mouse(buttons, NUM_BUTTONS, &button_selector);
    if (button_selected != NO_OPTION) 
    {
        reset_button_selector();
        button_hoover[button_selected] = true;
        return button_selected;
    }

    // SELEÇÃO DO MENU DE PAUSA POR TECLADO
    button_selected = read_keyboard(NUM_BUTTONS, &button_selector);

    if (button_selected != NO_OPTION) reset_button_selector();

    button_hoover[button_selector] = true;

    return button_selected;
}

Game_state pause_to_game_state(Pause_options pause_option)
{

    switch (pause_option)
    {
        case PAUSE_CONTINUE_GAME:
            return PLAYING;

        case PAUSE_RETURN_TO_MENU:
            return MENU;

        case PAUSE_EXIT_GAME:
            return EXIT;
        
        default:
            return PAUSED;
    }
}

void draw_menu_pause() {
    
    DrawText("PAUSE MENU", 10, 10, 40, BLACK);

    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        DrawRectangleRec(buttons[i], button_hoover[i] ? RED : GRAY);
    }

    DrawText("CONTINUE GAME", 100, 150, 20, BLACK);
    DrawText("RETURN TO MENU", 100, 210, 20, BLACK);
    DrawText("EXIT", 100, 270, 20, BLACK);
}