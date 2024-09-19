// player.c
#include "player.h"
#include <math.h>
#include <SDL2/SDL.h>

void handlePlayerInput(Game *game) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W]) {
        game->player.x += game->player.dirX * game->player.speed;
        game->player.y += game->player.dirY * game->player.speed;
    }
    if (state[SDL_SCANCODE_S]) {
        game->player.x -= game->player.dirX * game->player.speed;
        game->player.y -= game->player.dirY * game->player.speed;
    }
    if (state[SDL_SCANCODE_A]) {
        // Rotate player left
        float oldDirX = game->player.dirX;
        game->player.dirX = game->player.dirX * cos(0.05) - game->player.dirY * sin(0.05);
        game->player.dirY = oldDirX * sin(0.05) + game->player.dirY * cos(0.05);
    }
    if (state[SDL_SCANCODE_D]) {
        // Rotate player right
        float oldDirX = game->player.dirX;
        game->player.dirX = game->player.dirX * cos(-0.05) - game->player.dirY * sin(-0.05);
        game->player.dirY = oldDirX * sin(-0.05) + game->player.dirY * cos(-0.05);
    }
}

void updatePlayerPosition(Game *game) {
    // Implement collision detection logic here
    if (game->maze[(int)(game->player.y)][(int)(game->player.x)] == 1) {
        // Collision detected, adjust player position accordingly
        game->player.x -= game->player.dirX * game->player.speed;
        game->player.y -= game->player.dirY * game->player.speed;
    }
}
