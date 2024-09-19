// main.c
#include "game.h"
#include "player.h"
#include "render.h"

int main(int argc, char *argv[]) {
    Game game;
    if (initGame(&game) != 0) {
        return 1;
    }

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        handlePlayerInput(&game);
        updatePlayerPosition(&game);
        renderGame(&game);

        SDL_Delay(16);  // Cap the frame rate to ~60fps
    }

    freeGame(&game);
    return 0;
}
