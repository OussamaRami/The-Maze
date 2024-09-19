#ifndef CLOSE_H
#define CLOSE_H

#include "headers.h"
#include "defined.h"


void freeGame(Game *game) {
    SDL_DestroyTexture(game->texture);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}


#endif