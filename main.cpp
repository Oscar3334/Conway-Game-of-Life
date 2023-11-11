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
    
    int max_game_loops = 50;

    //game loops
    while (max_game_loops >= 0) {
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        camera->drawGrid(renderer, grid);
        camera->move(7.5, 7.5);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        
        grid->update();

        max_game_loops--;
    }
        
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
