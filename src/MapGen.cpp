#include "MapGen.h"

using RowBool = vector<bool>;


int MapGen::randMax(int max) {
    int n = rand() % max;
    return n;
}

int MapGen::boardCoord(int n) {
    return 2*n + 1;
}


// Initialize data structures and generate maze
MapGen::MapGen(int h, int w) {
    assert(h >= 5);
    assert(w >= 5);
    assert(h%2 == 1);
    assert(w%2 == 1);

    height = h/2;
    width = w/2;

    boardHeight = boardCoord(height);
    boardWidth = boardCoord(width);
    
    using RowCell = vector<Cell>;
    cells = vector<RowCell>(height, RowCell(width));
    board = vector<RowBool>(boardHeight, RowBool(boardWidth));
    
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            cells[r][c].row = r;
            cells[r][c].column = c;
        }
    }
    for (int r = 0; r < boardHeight; r++) {
        for (int c = 0; c < boardWidth; c++) {
            board[r][c] = (!(r&1) || !(c&1));
        }
    }

    current = &cells[randMax(height)][randMax(width)];

    generateMap();
}

// Recursive Backtracking
void MapGen::generateMap() {
    do {
        current->visited = true;
        Cell *next = findNextCell();

        if (next != NULL) {
            backtrace.push(current);
            removeWall(*current, *next);
            current = next;
        } else {
            current = backtrace.top();
            backtrace.pop();
        }
    }
    while (not backtrace.empty());
}

MapGen::Cell *MapGen::findNextCell() {
    vector<Cell *> neighbors = getAvailableNeighbors();
    if (not neighbors.empty()) {
        return neighbors[randMax(neighbors.size())];
    }

    return NULL;
}

vector<MapGen::Cell *> MapGen::getAvailableNeighbors() {
    vector<Cell *> neighbors;
    int cr = current->row;
    int cc = current->column;

    if (isValid(cr+1, cc)) neighbors.push_back(&cells[cr+1][cc]);
    if (isValid(cr-1, cc)) neighbors.push_back(&cells[cr-1][cc]);
    if (isValid(cr, cc+1)) neighbors.push_back(&cells[cr][cc+1]);
    if (isValid(cr, cc-1)) neighbors.push_back(&cells[cr][cc-1]);

    return neighbors;
}

bool MapGen::isValid(int r, int c) {
    return not (r < 0 or c < 0 or c > width-1 or r > height-1 or cells[r][c].visited);
}

void MapGen::removeWall(Cell &a, Cell &b) {
    int row = boardCoord(a.row);
    int col = boardCoord(a.column);
    int deltaRow = b.row - a.row;
    int deltaCol = b.column - a.column;

    // Remove wall
    board[row+deltaRow][col+deltaCol] = false;
}


void MapGen::addExtraPaths(int probExtraPath, bool removeIsolated) {
    assert(probExtraPath > 0);

    for (int r = 1; r < boardHeight-1; r++) {
        for (int c = 1; c < boardWidth-1; c++) {
            bool isWall = board[r][c];
            bool yPath = not board[r][c-1] and not board[r][c+1];
            bool xPath = not board[r-1][c] and not board[r+1][c];
            bool yWall = board[r][c-1] and board[r][c+1];
            bool xWall = board[r-1][c] and board[r+1][c];
            
            if (isWall and xPath and yWall and randMax(100) < probExtraPath) board[r][c] = false;
            if (isWall and yPath and xWall and randMax(100) < probExtraPath) board[r][c] = false;
        }
    }

    if (removeIsolated) {
        for (int r = 1; r < boardHeight-1; r++) {
            for (int c = 1; c < boardWidth-1; c++) {
                bool yPath = not board[r][c-1] and not board[r][c+1];
                bool xPath = not board[r-1][c] and not board[r+1][c];
                
                if (xPath and yPath) board[r][c] = false;
            }
        }
    }
}


vector<RowBool> MapGen::getMap() const {
    return board;
}
