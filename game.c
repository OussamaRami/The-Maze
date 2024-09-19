// game.c
#include "game.h"
#include "player.h"
#include "render.h"
#include <SDL2/SDL_image.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

int initGame(Game *game) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    game->window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (game->window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 1;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, 0);
    if (game->renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

    game->texture = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_RGBA8888,
                                      SDL_TEXTUREACCESS_TARGET,
                                      SCREEN_WIDTH, SCREEN_HEIGHT);
    if (game->texture == NULL) {
        printf("SDL_CreateTexture Error: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize the player
    game->player.x = 1.5;
    game->player.y = 1.5;
    game->player.dirX = 0;
    game->player.dirY = -1;
    game->player.planeX = 0.50;
    game->player.planeY = 0;
    game->player.speed = 0.5;

    // Load wall texture
    SDL_Surface *wallSurface = SDL_LoadBMP("tsawr/G10.bmp");
    if (!wallSurface) {
        printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
        return 1;
    }
    game->wallTexture.texture = SDL_CreateTextureFromSurface(game->renderer, wallSurface);
    SDL_FreeSurface(wallSurface);

    // Load floor texture
    SDL_Surface *floorSurface = SDL_LoadBMP("tsawr/G0.bmp");
    if (!floorSurface) {
        printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
        return 1;
    }
    game->floorTexture.texture = SDL_CreateTextureFromSurface(game->renderer, floorSurface);
    SDL_FreeSurface(floorSurface);

    // Initialize the maze (1 = wall, 0 = empty space)
    int maze[MAP_HEIGHT][MAP_WIDTH] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    memcpy(game->maze, maze, sizeof(maze));
    
    return 0;
}

void freeGame(Game *game) {
    SDL_DestroyTexture(game->texture);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}

