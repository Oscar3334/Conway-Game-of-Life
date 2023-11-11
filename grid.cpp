#include "grid.hpp"
#include <fstream>

Grid::Grid(int numRows, int numCols, float tileX, float tileY) {
    this->numRows = numRows+2;
    this->numCols = numCols+2;
    current = std::vector<std::vector<bool>> (this->numRows, std::vector<bool> (this->numCols, 0));
    next    = std::vector<std::vector<bool>> (this->numRows, std::vector<bool> (this->numCols, 0));
    this->tileX = tileX;
    this->tileY = tileY;
}

Grid::Grid(std::ifstream& csv, float tileX, float tileY) {
    this->tileX = tileX;
    this->tileY = tileY;
    current = std::vector<std::vector<bool>> (1, std::vector<bool> (0, 0));
    std::string line;
    int i = 1;
    while (csv) {
        std::getline(csv, line);
        current.push_back(std::vector<bool>(1, 0));
        for (char j : line) {
            if (j == '0' || j == '1') {
                current[i].push_back(j == '1');
            }
        }
        current[i].push_back(0);
        i++;
    }
    current[0] = std::vector<bool> (current[1].size(), 0);
    current.push_back(std::vector<bool> (current[0].size(), 0));
    next = std::vector<std::vector<bool>> (current.size(), std::vector<bool> (current[1].size(), 0));
    numRows = current.size()-2;
    numCols = current[0].size()-2;
}

bool Grid::get(int row, int col) const {
    return current[row+1][col+1];
}
    
int Grid::rows() const {
    return numRows-2;
}

int Grid::cols() const {
    return numCols-2;
}

void Grid::set(int row, int col, bool state) {
    current[row+1][col+1] = state;
}

float Grid::tileWidth() const {
    return tileX;
}

float Grid::tileHeight() const {
    return tileY;
}

void Grid::update() {
    int rowLimit = numRows-1;
    int colLimit = numCols-1;
    for (int i = 1; i < rowLimit; i++) {
        for (int j = 1; j < colLimit; j++) {
            int count = current[i-1][j-1] + current[i-1][j] + current[i-1][j+1]
                     + current[i][j-1]                     + current[i][j+1]
                     + current[i+1][j-1] + current[i+1][j] + current[i+1][j+1];
            if (current[i][j]) {
                next[i][j] = (count == 2 || count == 3);
            } else {
                next[i][j] = count == 3;
            }
        }
    }
    std::swap(current, next);
}
