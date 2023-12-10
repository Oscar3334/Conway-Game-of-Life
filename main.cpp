#include "SDL2/SDL.h"
#include <time.h>
#include <vector>
#include "grid.hpp"
#include "camera.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std::chrono;

int main(int argc, char** argv) {
    constexpr int SCREEN_SIZE_X = 640;
    constexpr int SCREEN_SIZE_Y = 480;
    
    SDL_Init(SDL_INIT_EVERYTHING);
    
    SDL_Window* window = nullptr;
    window = SDL_CreateWindow(
        "Conway",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_SIZE_X,
        SCREEN_SIZE_Y,
        SDL_WINDOW_SHOWN
    );
    
    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    constexpr float TILE_SIZE_X = 20.0;
    constexpr float TILE_SIZE_Y = 20.0;
    
    Grid* grid;
    if (argc == 1) {
//        grid = new Grid(27, 10, TILE_SIZE_X, TILE_SIZE_Y);
        grid = new Grid(100, 10, TILE_SIZE_X, TILE_SIZE_Y);
    } else {
        std::ifstream csv (argv[1]);
        grid = new Grid(csv, TILE_SIZE_X, TILE_SIZE_Y);
        csv.close();
    }
    Camera* camera = new Camera(0, 0, window);
    
    float scale = 1.0;

    bool quit = 0;
    bool simulate = 0;
    bool step = 0;
    //game loop
    while (!quit) {
        auto ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        //events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.repeat) break;
                    switch (event.key.keysym.sym) {
                        case SDLK_SPACE:
                            simulate ^= 1;
                            break;
                        case SDLK_RETURN:
                            simulate = 0;
                            step = 1;
                            break;
                        case SDLK_EQUALS:
                            scale += .05;
                            break;
                        case SDLK_MINUS:
                            scale -= .05;
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (simulate != 0) break;
                    int row, col;
                    camera->mapMouseToGrid(
                        grid, scale,
                        event.button.x, event.button.y,
                        &row, &col
                    );
                    grid->change(row, col);
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }
        const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
        if (keyStates[SDL_SCANCODE_LEFT]) {
            camera->move(-5, 0);
        }
        if (keyStates[SDL_SCANCODE_RIGHT]) {
            camera->move(5, 0);
        }
        if (keyStates[SDL_SCANCODE_UP]) {
            camera->move(0, -5);
        }
        if (keyStates[SDL_SCANCODE_DOWN]) {
            camera->move(0, 5);
        }

        //state updates
        if (simulate || step) {
            grid->update();
            step = 0;
        }
        
        
        //render
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        camera->drawGrid(renderer, grid, scale);
        
        SDL_RenderPresent(renderer);
        //SDL_Delay(100);
        int timeDiff = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - (int) ms;
        //std::clog << "\rTime per frame: " << timeDiff << "ms, fps: " << 1000.0/timeDiff << "             ";
    }
        
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
