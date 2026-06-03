#include "raylib.h"
#include "player.h"
#include "map.h"
#include "save.h"

#include <stdbool.h>
#include <stdio.h>

// Constantes de física (você pode ajustar esses valores para mudar a sensação do pulo)
#define GRAVITY 600.0f      // Força que puxa o player para baixo
#define JUMP_FORCE -350.0f  // Força do pulo (negativo porque na tela o 'para cima' é diminuir o Y)

static bool is_solid_tile(char map[MAP_ROWS][MAP_COLS], float x, float y)
{
    int col = (int)(x / TILE_SIZE);
    int row = (int)(y / TILE_SIZE);

    if (y < 0 || y >= SCREEN_HEIGHT || x < 0 || x >= SCREEN_WIDTH)
    {
        return true;
    }
    return map[row][col] == 'Z';
}

static bool can_move_to(char map[MAP_ROWS][MAP_COLS], float x, float y, float width, float height)
{
    if (is_solid_tile(map, x, y)) return false;
    if (is_solid_tile(map, x + width - 1, y)) return false;
    if (is_solid_tile(map, x, y + height - 1)) return false;
    if (is_solid_tile(map, x + width - 1, y + height - 1)) return false;
    return true;
}

static bool is_ladder_start(char map[MAP_ROWS][MAP_COLS], float x, float y) 
{ 
    int row = (int) y / TILE_SIZE; 
    int col = (int) (x + (TILE_SIZE/2)) / TILE_SIZE;

    if (map[row][col] == 'S') 
    { 
        return true; 
    } 
    
    if (map[row][col] == 'S') 
    { 
        return true; 
    } 
    
    return false; 
}

static bool is_ladder_down(char map[MAP_ROWS][MAP_COLS], float x, float y)
{
    int row = (int) y / TILE_SIZE; 
    int col = (int) (x + (TILE_SIZE/2)) / TILE_SIZE;

    if (map[row][col] == 'D') 
    { 
        return true; 
    } 
    
    if (map[row][col] == 'D') 
    { 
        return true; 
    } 
    
    return false; 
}

static void align_player_ladder(Player *player)
{
    // Encontra a coluna da matriz correspondente ao centro do player
    int col = (int) (player->x + (TILE_SIZE/2)) / TILE_SIZE;

    // Descobre a coordenada X do primeiro pixel da coluna
    int ladder_x = col * TILE_SIZE;

    // Calcula o deslocamento necessário para alinhar o player com a escada
    // A diferença entre o primeiro pixel da escada e o do player é o quanto precisamos alinhar
    float align_offset = (float) ladder_x - player->x;

    // Aplica o alinhamento
    player->x += align_offset;
}

static void climb_ladder(Player *player, char map[MAP_ROWS][MAP_COLS], float dt) 
{
    float dy = 0;
    
    if (IsKeyDown(KEY_DOWN)) dy += LADDER_SPEED * dt;
    if (IsKeyDown(KEY_UP)) dy -= LADDER_SPEED * dt;
    
    // Verifica se o player colidiu com uma plataforma (ou saiu da tela por consequencia)
    if (is_solid_tile(map, player->x, player->y + dy + TILE_SIZE -1))
    {
        player->state = GROUNDED;

        // esse while evita que o player fique flutuando (alguns pixels acima da plataforma)
        while(!is_solid_tile(map, player->x, player->y + TILE_SIZE))
        {
            player->y++;
        }

        return;
    }

    // Verifica se o player chegou no topo da escada
    if (is_ladder_down(map, player->x, player->y + TILE_SIZE -1) && (dy < 0))
    {
        player->state = GROUNDED;

        // esse while evita que o player fique flutuando (alguns pixels acima da plataforma) ou que ele caia da escada
        while(!(is_ladder_down(map, player->x, player->y)))
        {
            player->y++;
        }
    
        return;
    }

    // Atualiza a posição vertical do player
    player->y += dy;
}

static void move_player_x(Player *player, char map[MAP_ROWS][MAP_COLS], float dx, float dt)
{
    // --- MOVIMENTO HORIZONTAL ---
    if (IsKeyDown(KEY_RIGHT)) dx += player->speed * dt;
    if (IsKeyDown(KEY_LEFT))  dx -= player->speed * dt;

    if (can_move_to(map, player->x + dx, player->y, player->width, player->height))
    {
        player->x += dx;
    }
}

Player create_player(char map[MAP_ROWS][MAP_COLS])
{
    Player player;
    player.x = 0;
    player.y = 0;
    player.width = TILE_SIZE;
    player.height = TILE_SIZE;
    player.speed = 180.0f;
    player.points = 0;
    
    // Inicializa as variáveis de física
    player.speed_y = 0.0f;
    player.is_grounded = false;
    
    // Inicializa o estado do jogador como no chão
    player.state = GROUNDED;

    // Inicializa as vidas do jogador
    player.lives = load_game_lives(3);
    
    for (int row = 0; row < MAP_ROWS; row++)
    {
        for (int col = 0; col < MAP_COLS; col++)
        {
            if (map[row][col] == 'P')
            {
                player.x = col * TILE_SIZE;
                player.y = row * TILE_SIZE;
                player.spawn_x = player.x; // Salva a posição de spawn do jogador
                player.spawn_y = player.y; // Salva a posição de spawn do jogador
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

    switch (player->state)
    {
        case GROUNDED:

            move_player_x(player, map, dx, dt);

            // Se o jogador apertar ESPAÇO, ele pula
            if (IsKeyPressed(KEY_SPACE))
            {
                player->state = AIRBORNE;
                
                player->speed_y = JUMP_FORCE;

                // Calcula a distância que ele quer andar no eixo Y neste frame
                float dy = player->speed_y * dt;

                if (can_move_to(map, player->x, player->y + dy, player->width, player->height))
                {
                    player->y += dy;
                }
            }

            // Se não tiver chão ou escada embaixo do jogador, ele cai
            if (can_move_to(map, player->x, player->y + TILE_SIZE, player->width, player->height) && (!is_ladder_down(map, player->x, player->y)))
            {
                player->state = AIRBORNE;
                // AQUI O PERSONAGEM ESPERA 1 FRAME PARA CAIR, ANTES ELE COMEÇAVA A CAIR INSTANTÂNEAMENTE
            }

            // ESCADA
        
            // Subir escada
            if (IsKeyDown(KEY_UP) && is_ladder_start(map, player->x, player->y)) 
            { 
                align_player_ladder(player);
                player->state = CLIMBING;
            }

            // Descer escada
            if (IsKeyDown(KEY_DOWN) && is_ladder_down(map, player->x, player->y))
            {
                align_player_ladder(player);
                player->state = CLIMBING;
            }

            break;

        case AIRBORNE:

            move_player_x(player, map, dx, dt);

            // Aplica a gravidade continuamente
            player->speed_y += GRAVITY * dt;

            // Calcula a distância que ele quer andar no eixo Y neste frame
            float dy = player->speed_y * dt;

            // Verifica se pode se mover no eixo y
            if (can_move_to(map, player->x, player->y + dy, player->width, player->height))
            {
                // Atualiza a posição vertical
                player->y += dy;
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
                    // Pousou no chão

                    // esse while evita que o player fique flutuando (alguns pixels acima da plataforma)
                    while(can_move_to(map, player->x, player->y + 1, player->width, player->height))
                    {
                        player->y++;
                    }

                    player->state = GROUNDED;
                    player->speed_y = 0; // enquanto o player estiver no chao, sua velocidade vertical será zero
                }
            }

            break;

        case CLIMBING:

            climb_ladder(player, map, dt);    

            break;
    }
}

void draw_player(Player player)
{
    DrawRectangle((int)player.x, (int)player.y, (int)player.width, (int)player.height, RED);
}