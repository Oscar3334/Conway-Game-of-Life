#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "grid.hpp"
#include "SDL2/SDL.h"

class Camera {
public:
    Camera(float x, float y, int width, int height);
    void go(float x, float y);
    void move(float deltaX, float deltaY);
    void drawGrid(SDL_Renderer* renderer, Grid* grid, float scale);
private:
    float x, y;
    float width, height;
};

#endif //CAMERA_HPP
