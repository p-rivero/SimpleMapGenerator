#include "MapGen.h"
#include <iostream>


using RowBool = vector<bool>;

void outputBoard(vector<RowBool> board) {
    for (RowBool row : board) {
        for (bool cell : row) std::cout << (cell ? "#" : " ") << '\t';
        std::cout << "\n";
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int height = 15;
    int width = 21;
    int probExtraWalls = 0;

    if (argc >= 3) {
        height = atoi(argv[1]);
        width = atoi(argv[2]);
        if (argc == 4) probExtraWalls = atoi(argv[3]);
    }

    vector<RowBool> board;
    MapGen map(height, width);
    board = map.getMap();

    std::cout << "Generated maze:\n";
    outputBoard(board);

    if (probExtraWalls > 0) {
        map.addExtraPaths(probExtraWalls, true);
        board = map.getMap();

        std::cout << "\n\nWith extra paths:\n";
        outputBoard(board);
    }
}
