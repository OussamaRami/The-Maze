#ifndef RENDER_H
#define RENDER_H

#include "headers.h"
#include "defined.h"

void renderGame(Game *game) {
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    int numRays = SCREEN_WIDTH;
    float rayDirX, rayDirY;
    int mapX, mapY;
    float deltaDistX, deltaDistY;
    float sideDistX, sideDistY;
    int stepX, stepY;
    int hit, side;
    float wallDist;

    for (int x = 0; x < numRays; ++x) {
        float cameraX = 2 * x / (float)SCREEN_WIDTH - 1;
        rayDirX = game->player.dirX + game->player.planeX * cameraX;
        rayDirY = game->player.dirY + game->player.planeY * cameraX;

        mapX = (int)game->player.x;
        mapY = (int)game->player.y;

        deltaDistX = fabs(1 / rayDirX);
        deltaDistY = fabs(1 / rayDirY);

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (game->player.x - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->player.x) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (game->player.y - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->player.y) * deltaDistY;
        }

        hit = 0;
        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (game->maze[mapY][mapX] > 0)
                hit = 1;
        }

        if (side == 0)
            wallDist = (mapX - game->player.x + (1 - stepX) / 2) / rayDirX;
        else
            wallDist = (mapY - game->player.y + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(SCREEN_HEIGHT / wallDist);
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT)
            drawEnd = SCREEN_HEIGHT - 1;

        // Calculate which X-coordinate of the texture to sample
        float wallX;  // X coordinate on the wall
        if (side == 0) wallX = game->player.y + wallDist * rayDirY;
        else           wallX = game->player.x + wallDist * rayDirX;
        wallX -= floor(wallX);  

        // X coordinate on the texture
        int texX = (int)(wallX * (float)TEXTURE_WIDTH);
        if (side == 0 && rayDirX > 0) texX = TEXTURE_WIDTH - texX - 1;
        if (side == 1 && rayDirY < 0) texX = TEXTURE_WIDTH - texX - 1;

        // Render the wall slice with texture mapping (optimized to draw a column)
        SDL_Rect srcRect = { texX, 0, 1, TEXTURE_HEIGHT };
        SDL_Rect destRect = { x, drawStart, 1, drawEnd - drawStart };
        SDL_RenderCopy(game->renderer, game->wallTexture.texture, &srcRect, &destRect);
    }

    SDL_RenderPresent(game->renderer);
}



#endif // RENDER_H