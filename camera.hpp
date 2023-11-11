#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "grid.hpp"
#include "SDL2/SDL.h"

class Camera {
public:
    Camera(float x, float y, SDL_Window* window);
    void go(float x, float y);
    void move(float deltaX, float deltaY);
    void drawGrid(SDL_Renderer* renderer, Grid* grid, float scale);
private:
    float x, y;
    SDL_Window* window;
};

#endif //CAMERA_HPP
