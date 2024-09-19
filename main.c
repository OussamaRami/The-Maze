#include "everything.h"

int main(int argc, char *argv[]) {
    // Initialize the game structure
    Game game;

    // Initialize SDL and the game environment
    if (initGame(&game) != 0) {
        return 1;  // Exit if initialization failed
    }

    bool running = true;  // The game loop control variable
    SDL_Event event;      // To handle events

    // Main game loop
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;  // Break the loop if quit event is triggered
            }
        }

        // Handle player input (keyboard events)
        handlePlayerInput(&game);

        // Update player position based on input
        updatePlayerPosition(&game);

        // Render the updated game state (the maze and player view)
        renderGame(&game);

        // Delay to control frame rate
        SDL_Delay(16);  // Approximately 60 FPS
    }

    // Clean up and free allocated resources
    freeGame(&game);

    return 0;
}