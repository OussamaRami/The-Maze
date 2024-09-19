// render.c
#include "render.h"

void renderGame(Game *game) {
    SDL_SetRenderTarget(game->renderer, game->texture);
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    // Render logic here, using game->wallTexture, game->floorTexture, etc.

    SDL_SetRenderTarget(game->renderer, NULL);
    SDL_RenderCopy(game->renderer, game->texture, NULL, NULL);
    SDL_RenderPresent(game->renderer);
}
