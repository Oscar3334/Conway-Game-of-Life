#include "grid.hpp"
#include <fstream>
#include <iostream>

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
    std::string line;
    std::getline(csv,line);
    current = std::vector<std::vector<bool>> (1, std::vector<bool> (line.size()+2, 0));
    int i = 1;
    while (true) {
        current.push_back(std::vector<bool>{0});
        for (char j : line) {
            if (j == '0' || j == '1') {
                current[i].push_back(j == '1');
            }
        }
        current[i].push_back(0);
        i++;
        if (csv) std::getline(csv, line);
        else break;
    }
    current.pop_back();
    current.push_back(std::vector<bool> (current[0].size(), 0));
    using namespace std;
    clog << current.size() << endl;
    clog << current[0].size() << endl;
    
    next = std::vector<std::vector<bool>> (current.size(), std::vector<bool> (current[1].size(), 0));
    numRows = current.size();
    numCols = current[0].size();
     for (auto& i : current) {
        for (int j = 0; j < i.size(); j++) {
            clog << i[j] << "";
        } clog << endl;
    }
     
    clog << endl;
    for (auto& i : next) {
        for (int j = 0; j < i.size(); j++) {
            clog << i[j] << "";
        } clog << endl;
    }
    this->numRows = current.size();
    this->numCols = current[0].size();
}

bool Grid::get(int row, int col) const {
    if (row >= numRows || col >= numCols) {
        using namespace std;
        clog << "row: " << row << " col: " << col << endl;
        return 0;
    }
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

void Grid::change(int row, int col) {
    current[row+1][col+1] = !current[row+1][col+1];
}
