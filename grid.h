#ifndef maze_grid_h
#define maze_grid_h

#include <stdbool.h>
#include <stdlib.h>

enum WallType {
    OPEN,
    CLOSED,
};

enum Direction { UP, RIGHT, DOWN, LEFT };

typedef struct {
    enum WallType top;
    enum WallType bottom;
    enum WallType left;
    enum WallType right;
    // Used by some algorithms to see if the cell has previously
    // been visited
    bool visited;
} MazeCell;

typedef struct {
    int width;
    int height;
    MazeCell *cells;
    int playerPosition;
    bool playerEnabled;
} MazeGrid;

void Maze_InitCell(MazeCell *cell);
void Maze_InitGrid(MazeGrid *grid, int width, int height);
void Maze_FreeGrid(MazeGrid *grid);

void Maze_ResetVisitedState(MazeGrid *grid);

int Maze_GetPosition(MazeGrid *grid, int position, enum Direction direction);
int Maze_HasNeighbor(MazeGrid *grid, int position, enum Direction direction);

int Maze_MovePlayerInDirection(MazeGrid *grid, enum Direction direction);

int Maze_RemoveWall(MazeGrid *grid, int position, enum Direction direction);

int Maze_IsPositionVisited(MazeGrid *grid, int position);

#endif