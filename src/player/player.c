#include "raylib.h"
#include "player.h"
#include "map.h"

// Constantes de física (você pode ajustar esses valores para mudar a sensação do pulo)
#define GRAVITY 600.0f      // Força que puxa o player para baixo
#define JUMP_FORCE -350.0f  // Força do pulo (negativo porque na tela o 'para cima' é diminuir o Y)

static int is_solid_tile(char map[MAP_ROWS][MAP_COLS], int row, int col)
{
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS)
    {
        return 1;
    }
    return map[row][col] == 'Z';
}

static int is_solid_at_pixel(char map[MAP_ROWS][MAP_COLS], float x, float y)
{
    int col = (int)(x / TILE_SIZE);
    int row = (int)(y / TILE_SIZE);
    return is_solid_tile(map, row, col);
}

static int can_move_to(char map[MAP_ROWS][MAP_COLS], float x, float y, float width, float height)
{
    if (is_solid_at_pixel(map, x, y)) return 0;
    if (is_solid_at_pixel(map, x + width - 1, y)) return 0;
    if (is_solid_at_pixel(map, x, y + height - 1)) return 0;
    if (is_solid_at_pixel(map, x + width - 1, y + height - 1)) return 0;
    return 1;
}

Player create_player(char map[MAP_ROWS][MAP_COLS])
{
    Player player;
    player.x = 0;
    player.y = 0;
    player.width = TILE_SIZE;
    player.height = TILE_SIZE;
    player.speed = 180.0f;
    
    // Inicializa as variáveis de física
    player.speed_y = 0.0f;
    player.is_grounded = false;

    for (int row = 0; row < MAP_ROWS; row++)
    {
        for (int col = 0; col < MAP_COLS; col++)
        {
            if (map[row][col] == 'P')
            {
                player.x = col * TILE_SIZE;
                player.y = row * TILE_SIZE;
                map[row][col] = ' ';
                return player;
            }
        }
    }
    return player;
}

void update_player(Player *player, char map[MAP_ROWS][MAP_COLS])
{
    float dt = GetFrameTime();
    float dx = 0.0f;

    // --- MOVIMENTO HORIZONTAL ---
    if (IsKeyDown(KEY_RIGHT)) dx += player->speed * dt;
    if (IsKeyDown(KEY_LEFT))  dx -= player->speed * dt;

    if (can_move_to(map, player->x + dx, player->y, player->width, player->height))
    {
        player->x += dx;
    }

    // --- FÍSICA DO PULO E GRAVIDADE (EIXO Y) ---
    
    // Aplica a gravidade continuamente se não estiver no chão
    player->speed_y += GRAVITY * dt;

    // Se o jogador apertar ESPAÇO (ou KEY_UP) E estiver tocando o chão, ele pula
    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) && player->is_grounded)
    {
        player->speed_y = JUMP_FORCE;
        player->is_grounded = false;
    }

    // Calcula a distância que ele quer andar no eixo Y neste frame
    float dy = player->speed_y * dt;

    // Tenta mover no eixo Y
    if (can_move_to(map, player->x, player->y + dy, player->width, player->height))
    {
        player->y += dy;
        
        // Se ele está se movendo para baixo, precisamos checar se bateu no chão
        // Fazemos isso testando se 1 pixel abaixo dele é sólido
        if (player->speed_y >= 0 && !can_move_to(map, player->x, player->y + 1, player->width, player->height))
        {
            // player em cima da plataforma
            player->is_grounded = true;
            player->speed_y = 0;
        }
        else
        {
            // player pode continuar caindo
            player->is_grounded = false;
        }
    }
    else
    {
        // Se ele NÃO pôde se mover, significa que colidiu com um teto (subindo) ou chão (descendo)
        if (player->speed_y < 0)
        {
            // Bateu a cabeça no teto: zera a velocidade para começar a cair imediatamente
            player->speed_y = 0; 
        }
        else if (player->speed_y > 0)
        {
            // Pousou no chão ou está parado
            player->is_grounded = true;
            player->speed_y = 0; // enquanto o player estiver no chao, sua velocidade vertical será zero
        }
    }
}

void draw_player(Player player)
{
    DrawRectangle((int)player.x, (int)player.y, (int)player.width, (int)player.height, RED);
}