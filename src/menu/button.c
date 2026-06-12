#include "button.h"
#include "raylib.h"

int read_mouse(Rectangle buttons[], const int num_buttons, int *button_selector)
{
    Vector2 mouse_position = GetMousePosition();

    // Verifica se houve colisão do mouse com cada um dos num_buttons botões
    for (int i = 0; i < num_buttons; i++)
    {
        if (CheckCollisionPointRec(mouse_position, buttons[i]))
        {
            *button_selector = i;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                return *button_selector;
            }
        }
    }

    return NO_BUTTON_SELECTED;
}

int read_keyboard(const int num_buttons, int *button_selector)
{
    if (IsKeyPressed(KEY_UP))
    {
        // Se o botão atualmente em foco não for o primeiro e eu tenho um jogo ativo
        if (((*button_selector) > 0))
        {
            // Move o foco para o botão anterior (subir no menu)
            (*button_selector)--;
        }
        else
        {
            // Efeito "Loop": Se estiver no topo (primeiro botão), move o foco para o último botão
            *button_selector = num_buttons - 1;
        }
    }

    if (IsKeyPressed(KEY_DOWN))
    {
        // Se o botão atualmente em foco não for o último
        if ((*button_selector) < num_buttons - 1)
        {
            // Move o foco para o próximo botão (descer no menu)
            (*button_selector)++;
        }
        else
        {
            // Efeito "Loop": Volta para o início do menu (botão 0 (CONTINUE) se houver jogo ativo, ou pula para o botão 1 (NEW GAME))
            *button_selector = 0;
        }
    }

    // Seleciona a opção do menu equivalente ao "index" do botão selecionado (as opções do menu são um enum)
    if (IsKeyPressed(KEY_ENTER))
    {
        return *button_selector;
    }

    return NO_BUTTON_SELECTED;
}