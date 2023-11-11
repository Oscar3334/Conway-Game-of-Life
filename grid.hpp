#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

class Grid {
public:
    Grid(int, int, float, float);
    void set(int, int, bool);
    void update();
    bool get(int, int) const;
    int rows() const;
    int cols() const;
    float tileWidth() const;
    float tileHeight() const;
private:
    int numRows, numCols;
    float tileX, tileY;
    std::vector<std::vector<bool>> current, next;
};

#endif //GRID_HPP
