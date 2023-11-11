#include "camera.hpp"
#include "grid.hpp"
#include "SDL2/SDL.h"
#include <cmath>

Camera::Camera(float x, float y, int width, int height) {
    this->go(x,y);
    this->width = (float) width;
    this->height = (float) height;
}

void Camera::go(float x, float y) {
    this->x = x;
    this->y = y;
}

void Camera::move(float deltaX, float deltaY) {
    x += deltaX;
    y += deltaY;
}

void Camera::drawGrid(SDL_Renderer* renderer, Grid* grid) {
    float tileX  = grid->tileWidth();
    float tileY  = grid->tileHeight();
    float startX = -std::fmod(x, tileX);
    float startY = -std::fmod(y, tileY);
    int startRow = y / tileY;
    int startCol = x / tileX;
    int numRows  = (int) std::ceil((height - startY)/ tileY);
    int numCols  = (int) std::ceil((width - startX) / tileX);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (grid->get(startRow+i,startCol+j)) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_FRect rect = {startX + j*tileX, startY + i*tileY, tileX, tileY};
            rect.w -= 1.0;
            rect.h -= 1.0;
            SDL_RenderFillRectF(renderer, &rect);
        }
    }
}
