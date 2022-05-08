#include "MapGen.h"
#include <iostream>


using RowBool = vector<bool>;

// Print a boolean matrix to the terminal
void outputBoard(const vector<RowBool>& board) {
    for (RowBool row : board) {
        for (bool cell : row) std::cout << (cell ? "#" : " ") << '\t';
        std::cout << "\n";
    }
}

int main(int argc, char **argv) {
    // Default values
    int height = 15;
    int width = 21;
    int probExtraWalls = 0;

    if (argc >= 3) {
        height = atoi(argv[1]); // First argument: height of the generated map
        width = atoi(argv[2]);  // Second argument: width of the generated map
    }
    if (argc >= 4) probExtraWalls = atoi(argv[3]);

    vector<RowBool> board;
    MapGen map(height, width);  // Generate the maze

    // Print the maze
    board = map.getMap();
    std::cout << "Generated maze:\n";
    outputBoard(board);

    // If a third argument is provided, remove extra walls and print result
    if (probExtraWalls > 0) {
        map.addExtraPaths(probExtraWalls, true);
        board = map.getMap();

        std::cout << "\n\nWith extra paths:\n";
        outputBoard(board);
    }
}
