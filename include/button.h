#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"

// Padronização de botões
#define BUTTON_WIDTH 200  // Largura do botão
#define BUTTON_HEIGHT 50  // Altura do botão
#define PADDING 10        // Espaço entre os botões

#define NO_BUTTON_SELECTED -1

int read_mouse(Rectangle buttons[], const int num_buttons, int *button_selector);
int read_keyboard(const int num_buttons, int *button_selector);

#endif