#ifndef MAPGEN_H
#define MAPGEN_H

#include <stack>
#include <vector>
#include <stdlib.h>
#include <assert.h>
#include <random>

using std::vector;
using std::stack;

class MapGen {
private:
    int height;
    int width;
    int boardHeight;
    int boardWidth;

    struct Cell {
        int row;
        int column;
        bool visited = false;
    };

    vector<vector<Cell>> cells;
    vector<vector<bool>> board;
    Cell *current;

    static unsigned long randMax(unsigned long max);
    static inline int boardCoord(int max);
    inline bool isValid(int i, int j) const;
    void generateMap();
    Cell* findNextCell();
    vector<Cell*> getAvailableNeighbors();
    void removeWall(const Cell &a, const Cell &b);
    void removeIsolatedCells();

public:
    // Generate a maze with the desired height and width
    MapGen(int height, int width);
    // Remove some walls from the maze
    void addExtraPaths(int probExtraPath = 20, bool removeIsolated = true);
    // Get the resulting boolean matrix
    vector<vector<bool>> getMap() const;
};

#endif
