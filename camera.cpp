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

void Camera::drawGrid(SDL_Renderer* renderer, Grid* grid, float scale) {
    const float borderPercent = .025;
    float tileX  = scale * grid->tileWidth();
    float tileY  = scale * grid->tileHeight();
    float startX = -std::fmod(x, tileX);
    float startY = -std::fmod(y, tileY);
    int startRow = y / tileY;
    int startCol = x / tileX;
    int numRows  = (int) std::ceil((height - startY)/ tileY);
    int numCols  = (int) std::ceil((width - startX) / tileX);
    int rowOffset = 0;
    int colOffset = 0;
    if (startRow < 0) {
        numRows += startRow;
        rowOffset-=startRow;
        startRow = 0;
    }
    if (startRow + numRows > grid->rows()) {
        numRows -= startRow + numRows - grid->cols();
    }
    if (startCol < 0) {
        numCols += startCol;
        colOffset-=startCol;
        startCol = 0;
    }
    if (startCol + numCols > grid->cols()) {
        numCols -= startCol + numCols - grid->cols();
    }
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (grid->get(startRow+i,startCol+j)) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_FRect rect = {
                startX + (j+colOffset-borderPercent)*tileX,
                startY + (i+rowOffset-borderPercent)*tileY,
                (1-borderPercent*2)*tileX,
                (1-borderPercent*2)*tileY};
            SDL_RenderFillRectF(renderer, &rect);
        }
    }
}
