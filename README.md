# Simple Map Generator

`MapGen` is a simple and lightweight C++ class that generates maze-like maps for tile-based games.

The output is a *matrix of booleans*, in which `true` is a wall and `false` is a walkable tile.


## Usage
1. Create a `MapGen` object. You need to provide the height and width of the desired output matrix. Keep in mind that most of the work is done in this step.
    
    ```c++
    int height = 21;
    int width = 15;
    MapGen map(height, width);
    ```

    > **Warning:** The method currently used for generating the maze requires both of those sizes to be *odd numbers*. The minimum supported size is 5x5.

2. If your game/application requires an actual maze, you can skip this step. If you want a maze-like structure but easier to traverse (with extra corridors), call `addExtraPaths()`.

    ```c++
    int probExtraPath = 30;     // Probability of deleting a candidate wall (percent)
    bool removeIsolated = true; // If true, all remaining 1x1 walls will be deleted
    map.addExtraPaths(probExtraWalls, removeIsolated);
    ```

3. Get the resulting boolean matrix. Unfortunately C++ doesn't support variable-size arrays, so I had to use `std::vector` instead.
    ```c++
    std::vector< std::vector<bool> > result = map.getMap();
    ```


## Example
`main.cpp` contains a small example program. You can build it with `g++ src/*.cpp -o mapGenExample`.

A possible output of `./mapGenExample 21 21 30` (height 21, width 21, 30% chance of deleting wall) is:

<details>
  <summary>Click to see actual console output</summary>
  
```
Generated maze:
#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	
#	 	#	 	 	 	 	 	#	 	 	 	#	 	 	 	 	 	 	 	#	
#	 	#	 	#	 	#	 	#	 	#	 	#	 	#	#	#	#	#	 	#	
#	 	#	 	#	 	#	 	#	 	#	 	 	 	#	 	 	 	 	 	#	
#	 	#	 	#	 	#	 	#	 	#	#	#	#	#	 	#	#	#	#	#	
#	 	 	 	#	 	#	 	 	 	#	 	#	 	 	 	#	 	 	 	#	
#	#	#	#	#	 	#	#	#	#	#	 	#	 	#	#	#	 	#	 	#	
#	 	 	 	 	 	#	 	 	 	 	 	#	 	#	 	 	 	#	 	#	
#	 	#	#	#	#	#	 	#	 	#	#	#	 	#	 	#	 	#	#	#	
#	 	#	 	 	 	#	 	#	 	#	 	 	 	#	 	#	 	 	 	#	
#	 	#	 	#	 	#	 	#	#	#	 	#	#	#	 	#	#	#	 	#	
#	 	#	 	#	 	#	 	 	 	 	 	#	 	 	 	#	 	 	 	#	
#	 	#	#	#	 	#	 	#	#	#	#	#	 	#	#	#	 	#	#	#	
#	 	 	 	#	 	#	 	#	 	 	 	 	 	 	 	#	 	 	 	#	
#	 	#	#	#	 	#	 	#	#	#	#	#	#	#	 	#	#	#	 	#	
#	 	 	 	#	 	#	 	 	 	 	 	#	 	 	 	#	 	#	 	#	
#	#	#	 	#	 	#	#	#	#	#	 	#	#	#	 	#	 	#	 	#	
#	 	 	 	#	 	 	 	 	 	#	 	 	 	#	 	 	 	#	 	#	
#	 	#	#	#	#	#	#	#	 	#	#	#	 	#	#	#	#	#	 	#	
#	 	 	 	 	 	 	 	 	 	#	 	 	 	 	 	 	 	 	 	#	
#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	


With extra paths:
#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	
#	 	#	 	 	 	 	 	#	 	 	 	 	 	 	 	 	 	 	 	#	
#	 	#	 	#	 	#	 	#	 	 	 	 	 	#	#	#	#	#	 	#	
#	 	#	 	#	 	#	 	#	 	 	 	 	 	#	 	 	 	 	 	#	
#	 	#	 	#	 	#	 	#	 	#	 	#	#	#	 	#	#	 	#	#	
#	 	 	 	 	 	#	 	 	 	#	 	#	 	 	 	 	 	 	 	#	
#	 	 	 	 	 	#	#	#	#	#	 	#	 	#	 	 	 	#	 	#	
#	 	 	 	 	 	#	 	 	 	 	 	 	 	#	 	 	 	#	 	#	
#	 	#	#	#	#	#	 	 	 	#	#	#	 	#	 	#	 	#	#	#	
#	 	#	 	 	 	 	 	 	 	#	 	 	 	 	 	#	 	 	 	#	
#	 	#	 	#	 	#	 	 	 	#	 	#	#	#	 	#	 	 	 	#	
#	 	#	 	#	 	#	 	 	 	 	 	#	 	 	 	#	 	 	 	#	
#	 	#	#	#	 	#	 	#	#	#	#	#	 	 	 	#	 	 	 	#	
#	 	 	 	#	 	#	 	 	 	 	 	 	 	 	 	#	 	 	 	#	
#	 	#	#	#	 	#	 	#	#	#	 	#	#	#	 	#	#	#	 	#	
#	 	 	 	 	 	 	 	 	 	 	 	#	 	 	 	#	 	#	 	#	
#	 	 	 	#	 	#	#	#	#	#	 	#	#	#	 	#	 	#	 	#	
#	 	 	 	#	 	 	 	 	 	#	 	 	 	#	 	 	 	#	 	#	
#	 	#	#	#	 	#	#	#	 	#	#	#	 	#	 	 	 	#	 	#	
#	 	 	 	 	 	 	 	 	 	#	 	 	 	 	 	 	 	 	 	#	
#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	#	
```
</details>

![Demo](https://github.com/p-rivero/SimpleMapGenerator/blob/main/img/demo.png?raw=true)


## How it works
The maze is generated using the *recursive backtracker algorithm* with a small twist. You can learn about the basic version [here](https://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking).

My implementation uses 2 matrices or *spaces*:

- **Cell space**: A grid of cells. Each cell knows (1) its coordinates in the grid and (2) whether it has already been visited. This is where the algorithm proper is performed.

- **Board space**: A matrix of booleans (tiles that can be walkable/`false` or wall/`true`). Once the algorithm ends, this matrix contains the generated maze.

There's a direct mapping from cell space to board space (see diagram below):
1. Each cell *always* becomes a walkable tile. A cell `(x,y)` gets mapped to the board position `(2*x+1, 2*y+1)`.
2. Tiles that are diagonal to cells will *always* be a wall.
3. Tiles that connect 2 cells can either be a wall or not. All of them begin as walls and the algorithm calls `removeWall()` between 2 cells to progressively carve the maze.

This mapping is the reason why the result matrix always has odd height and width.

The rest of the algorithm (traversing the cell grid and removing walls between cells) is identical to the basic version of this algorithm.
Once the maze has been generated, removing some walls is trivial and requires a single pass on the result matrix.

![Spaces diagram](https://github.com/p-rivero/SimpleMapGenerator/blob/main/img/spaces.png?raw=true)
