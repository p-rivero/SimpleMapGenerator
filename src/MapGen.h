#ifndef GRID_H
#define GRID_H

#include <stack>
#include <vector>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

using std::vector;
using std::stack;

class MapGen {
private:
    int height;
    int width;
    int boardHeight;
    int boardWidth;

    struct Cell {
        int row, column;
        bool visited = false;
    };

    vector<vector<Cell>> cells;
    vector<vector<bool>> board;
    stack<Cell*> backtrace;
    Cell *current;

    static inline int randMax(int max);
    static inline int boardCoord(int max);
    inline bool isValid(int i, int j);
    void generateMap();
    Cell* findNextCell();
    vector<Cell*> getAvailableNeighbors();
    void removeWall(Cell &a, Cell &b);

public:
    MapGen(int height, int width);
    void addExtraPaths(int probExtraPath = 20, bool removeIsolated = true);
    vector<vector<bool>> getMap() const;
};

#endif
