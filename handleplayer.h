#ifndef HANDLEPLAYER_H
#define HANDLEPLAYER_H

#include "headers.h"
#include "defined.h"


void handlePlayerInput(Game *game) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    float moveSpeed = game->player.speed * 0.1;
    float rotSpeed = 0.03;  // Rotation speed

    float oldX = game->player.x;
    float oldY = game->player.y;

    // Move forward or backward
    if (state[SDL_SCANCODE_W]) {
        float newX = game->player.x + game->player.dirX * moveSpeed;
        float newY = game->player.y + game->player.dirY * moveSpeed;

        // Check for collision with front buffer zone
        if (game->maze[(int)(newY + game->player.dirY * moveSpeed * 0.5)][(int)(newX + game->player.dirX * moveSpeed * 0.5)] == 0 &&
            game->maze[(int)(newY - game->player.dirY * moveSpeed * 0.5)][(int)(newX - game->player.dirX * moveSpeed * 0.5)] == 0 &&
            game->maze[(int)(newY + game->player.dirY * 0.5)][(int)(newX + game->player.dirX * 0.5)] == 0 &&
            game->maze[(int)(newY - game->player.dirY * 0.5)][(int)(newX - game->player.dirX * 0.5)] == 0) {
            game->player.x = newX;
            game->player.y = newY;
        }
    }
    if (state[SDL_SCANCODE_S]) {
        float newX = game->player.x - game->player.dirX * moveSpeed;
        float newY = game->player.y - game->player.dirY * moveSpeed;

        // Check for collision with rear buffer zone
        if (game->maze[(int)(newY + game->player.dirY * moveSpeed * 0.5)][(int)(newX + game->player.dirX * moveSpeed * 0.5)] == 0 &&
            game->maze[(int)(newY - game->player.dirY * moveSpeed * 0.5)][(int)(newX - game->player.dirX * moveSpeed * 0.5)] == 0 &&
            game->maze[(int)(newY + game->player.dirY * 0.5)][(int)(newX + game->player.dirX * 0.5)] == 0 &&
            game->maze[(int)(newY - game->player.dirY * 0.5)][(int)(newX - game->player.dirX * 0.5)] == 0) {
            game->player.x = newX;
            game->player.y = newY;
        }
    }

    // Rotate left
    if (state[SDL_SCANCODE_A]) {
        float oldDirX = game->player.dirX;
        game->player.dirX = game->player.dirX * cos(-rotSpeed) - game->player.dirY * sin(-rotSpeed);
        game->player.dirY = oldDirX * sin(-rotSpeed) + game->player.dirY * cos(-rotSpeed);

        float oldPlaneX = game->player.planeX;
        game->player.planeX = game->player.planeX * cos(-rotSpeed) - game->player.planeY * sin(-rotSpeed);
        game->player.planeY = oldPlaneX * sin(-rotSpeed) + game->player.planeY * cos(-rotSpeed);
    }

    // Rotate right
    if (state[SDL_SCANCODE_D]) {
        float oldDirX = game->player.dirX;
        game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
        game->player.dirY = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);

        float oldPlaneX = game->player.planeX;
        game->player.planeX = game->player.planeX * cos(rotSpeed) - game->player.planeY * sin(rotSpeed);
        game->player.planeY = oldPlaneX * sin(rotSpeed) + game->player.planeY * cos(rotSpeed);
    }
}

void updatePlayerPosition(Game *game) {
    // Player position is updated in handlePlayerInput
}


#endif // HANDLEPLAYER_H