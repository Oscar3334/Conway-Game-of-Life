#include "SDL2/SDL.h"
#include <time.h>
#include <vector>
#include "grid.hpp"
#include "camera.hpp"

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
    
    Grid* grid = new Grid(100, 100, TILE_SIZE_X, TILE_SIZE_Y);
    Camera* camera = new Camera(0.0, 0.0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
    
    grid->set(3, 4, 1);
    grid->set(4, 5, 1);
    grid->set(5, 5, 1);
    grid->set(5, 4, 1);
    grid->set(5, 3, 1);
    
    bool quit = 0;
    bool simulate = 0;
    bool step = 0;
    //game loop
    while (!quit) {
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
                            step = 1;
                            break;
                        default:
                            break;
                    }
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
        
        camera->drawGrid(renderer, grid);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);

    }
        
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
