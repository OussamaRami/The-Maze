#ifndef DEFINED_H
#define DEFINED_H

#include "headers.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700
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

int initGame(Game *game);
void handlePlayerInput(Game *game);
void updatePlayerPosition(Game *game);
void renderGame(Game *game);
void freeGame(Game *game);

#endif // defined files
