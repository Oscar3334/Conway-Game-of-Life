#include "SDL2/SDL.h"
#include <time.h>
#include <vector>

void drawTiles(SDL_Renderer* renderer, int startX, int startY, std::vector<std::vector<bool>>& tiles, int tileSizeX, int tileSizeY) {
    for (int i = 0; i < tiles.size(); i++) {
        for (int j = 0; j < tiles[0].size(); j++) {
            if (tiles[i][j]) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_Rect rect = {startX + j*tileSizeX, startY + i*tileSizeY, tileSizeX-1, tileSizeY-1};
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void generateNextState(std::vector<std::vector<bool>>& cur, std::vector<std::vector<bool>>& next) {
    for (int i = 0; i < cur.size(); i++) {
        for (int j = 0; j < cur[0].size(); j++) {
            int cnt = 0;
            if (i != 0) cnt += cur[i-1][j];
            if (j != 0) cnt += cur[i][j-1];
            if (i != 0 && j != 0) cnt += cur[i-1][j-1];
            if (i != cur.size()-1 && j != 0) cnt += cur[i+1][j-1];
            if (i != cur.size()-1) cnt += cur[i+1][j];
            if (i != cur.size()-1 && j != cur[0].size()-1) cnt += cur[i+1][j+1];
            if (j != cur[0].size()-1) cnt += cur[i][j+1];
            if (i != 0 && j != cur[0].size()-1) cnt += cur[i-1][j+1];

            if (cur[i][j] == 0) {
                next[i][j] = cnt == 3;
            } else {
                next[i][j] = (cnt == 2 || cnt == 3);
            }
        }
    }
}

void drawBuffer(SDL_Renderer* renderer, int bufferX, int bufferY, int screenX, int screenY) {
    SDL_Rect left = {0, 0, bufferX-1, screenY};
    SDL_Rect right = {screenX-bufferX, 0, bufferX, screenY};
    SDL_Rect top = {0, 0, screenX, bufferY-1};
    SDL_Rect bottom = {0, screenY-bufferY, screenX, bufferY};
    SDL_RenderFillRect(renderer, &left);
    SDL_RenderFillRect(renderer, &right);
    SDL_RenderFillRect(renderer, &top);
    SDL_RenderFillRect(renderer, &bottom);
}

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
    
    constexpr int SCREEN_BUFFER_SIZE = 10;
    constexpr int TILE_SIZE_X = 20;
    constexpr int TILE_SIZE_Y = 20;
    
    constexpr int TILES_PER_ROW = (SCREEN_SIZE_X-SCREEN_BUFFER_SIZE*2)/TILE_SIZE_X;
    constexpr int TILES_PER_COLUMN = (SCREEN_SIZE_Y-SCREEN_BUFFER_SIZE*2)/TILE_SIZE_Y;
    
    std::vector<std::vector<bool>> grid (TILES_PER_COLUMN, std::vector<bool>(TILES_PER_ROW, 0));
    std::vector<std::vector<bool>> nextGrid (TILES_PER_COLUMN, std::vector<bool>(TILES_PER_ROW));
    
    int max_game_loops = 50;

    while (max_game_loops >= 0) {
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        drawBuffer(renderer, SCREEN_BUFFER_SIZE, SCREEN_BUFFER_SIZE, SCREEN_SIZE_X, SCREEN_SIZE_Y);
        
        drawTiles(renderer, SCREEN_BUFFER_SIZE, SCREEN_BUFFER_SIZE, grid, TILE_SIZE_X, TILE_SIZE_Y);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        
        generateNextState(grid, nextGrid);
        std::swap(grid, nextGrid);
        
        max_game_loops--;
    }
        
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
