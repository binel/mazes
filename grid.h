#ifndef maze_grid_h
#define maze_grid_h

#include <stdbool.h>
#include <stdlib.h>

/*
 * Describes if the wall of a cell exists or not
 */ 
enum WallType {
    OPEN,
    CLOSED,
};

/*
 * Cardinal directions 
 */
enum Direction { UP, RIGHT, DOWN, LEFT };

/*
 * Struct for a single cell of the maze
 */
typedef struct {
	// State of the top (north) wall
    enum WallType top;
    // State of the bottom (south) wall
    enum WallType bottom;
    // State of the left (west) wall
    enum WallType left;
    // State of the right (east) wall
    enum WallType right;
    // Used by some algorithms to see if the cell has previously
    // been visited
    // TODO split this out 
    bool visited;
} MazeCell;

/* 
 * Struct for holding the state of the maze
 */
typedef struct {
	// The width of the maze in cells
    int width;
    // The height of the maze in cells
    int height;
    // The cell array - there are width*height cells
    MazeCell *cells;
    // TODO split out the player stuff
    // The position is the maze that the player currently is 
    int playerPosition;
    // True if the player should be drawn 
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