#include "MapGen.h"

using RowBool = vector<bool>;


// Generate a random integer in [0, max-1]
int MapGen::randMax(int max) {
    return rand() % max;
}

// Convert from cell coordinates to board coordinates.
int MapGen::boardCoord(int n) {
    return 2*n + 1;
}


// Initialize data structures and generate maze
MapGen::MapGen(int h, int w) {
    // Ugly assertions, feel free to improve the error checking
    assert(h >= 5);
    assert(w >= 5);
    assert(h%2 == 1);
    assert(w%2 == 1);

    // Size of the cell grid
    height = h/2;
    width = w/2;

    // Size of the tile grid
    boardHeight = boardCoord(height);
    boardWidth = boardCoord(width);
    
    // Initialize matrices
    using RowCell = vector<Cell>;
    cells = vector<RowCell>(height, RowCell(width));
    board = vector<RowBool>(boardHeight, RowBool(boardWidth));
    
    // Each cell contains its coordinates in the grid
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            cells[r][c].row = r;
            cells[r][c].column = c;
        }
    }
    // Initialize board: the only tiles that are not walls (set to false) are
    // the cells (odd coordinates).
    for (int r = 0; r < boardHeight; r++) {
        for (int c = 0; c < boardWidth; c++) {
            board[r][c] = (!(r&1) || !(c&1));
        }
    }

    // Begin traversing the grid at a random start position
    current = &cells[randMax(height)][randMax(width)];

    generateMap();
}

// Recursive Backtracking
void MapGen::generateMap() {
    do {
        current->visited = true;        // Mark current cell as visited
        Cell *next = findNextCell();    // Find a random adjacent cell to visit next

        if (next != NULL) {
            backtrace.push(current);     // Store current cell to return later
            removeWall(*current, *next); // Remove wall between current and next cell
            current = next;
        }
        else {
            // No more available cells to visit: backtrack
            current = backtrace.top();
            backtrace.pop();
        }
    }
    while (not backtrace.empty());
}

// Select a non-visited adjacent cell to visit next
MapGen::Cell *MapGen::findNextCell() {
    // Get all non-visited adjacent cells
    vector<Cell *> neighbors = getAvailableNeighbors();
    if (not neighbors.empty()) {
        // If there's one or more, select a random one
        return neighbors[randMax(neighbors.size())];
    }

    return NULL;
}

// Get all non-visited cells that are adjacent to current
vector<MapGen::Cell *> MapGen::getAvailableNeighbors() {
    vector<Cell *> neighbors;   // List of available cells
    int cr = current->row;
    int cc = current->column;

    // For each of the 4 adjacent cells, check if it's valid and add to list 
    if (isValid(cr+1, cc)) neighbors.push_back(&cells[cr+1][cc]);
    if (isValid(cr-1, cc)) neighbors.push_back(&cells[cr-1][cc]);
    if (isValid(cr, cc+1)) neighbors.push_back(&cells[cr][cc+1]);
    if (isValid(cr, cc-1)) neighbors.push_back(&cells[cr][cc-1]);

    return neighbors;
}

// Return true if the cell located on a row+column exists and hasn't been visited
bool MapGen::isValid(int r, int c) {
    return not (r < 0 or c < 0 or c > width-1 or r > height-1 or cells[r][c].visited);
}

// Remove a wall (in the board) between 2 cells
void MapGen::removeWall(Cell &a, Cell &b) {
    int row = boardCoord(a.row);
    int col = boardCoord(a.column);
    int deltaRow = b.row - a.row;
    int deltaCol = b.column - a.column;

    // Remove wall
    board[row+deltaRow][col+deltaCol] = false;
}


// Called once the maze has been generated
void MapGen::addExtraPaths(int probExtraPath, bool removeIsolated) {
    assert(probExtraPath >= 0);

    for (int r = 1; r < boardHeight-1; r++) {
        for (int c = 1; c < boardWidth-1; c++) {
            bool yPath = not board[r][c-1] and not board[r][c+1];
            bool xPath = not board[r-1][c] and not board[r+1][c];
            bool yWall = board[r][c-1] and board[r][c+1];
            bool xWall = board[r-1][c] and board[r+1][c];
            
            // If there's a path in one axis and walls in the other axis,
            // this wall can be removed
            if (xPath and yWall and randMax(100) < probExtraPath) board[r][c] = false;
            if (yPath and xWall and randMax(100) < probExtraPath) board[r][c] = false;
        }
    }

    if (removeIsolated) {
        // Remove all remaining 1x1 walls (all 4 directions don't have walls)
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
