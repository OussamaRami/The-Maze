// game.h
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64
#define MAP_WIDTH 50
#define MAP_HEIGHT 50

typedef struct {
    float x, y;
    float dirX, dirY;
    float planeX, planeY;
    float speed;
} Player;

typedef struct {
    SDL_Texture *texture;
    int width, height;
} Texture;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    Player player;
    Texture wallTexture;
    Texture floorTexture;
    int maze[MAP_HEIGHT][MAP_WIDTH];
    int startX, startY;
    int endX, endY;
} Game;

// Game initialization and freeing functions
int initGame(Game *game);
void freeGame(Game *game);

#endif // GAME_H
