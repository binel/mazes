#ifndef maze_grid_h
#define maze_grid_h

#include <stdlib.h>

enum WallType {
	OPEN,
	CLOSED,
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef struct {
	enum WallType top;
	enum WallType bottom;
	enum WallType left; 
	enum WallType right; 
} MazeCell;

typedef struct {
	int width;
	int height; 
	MazeCell* cells;
} MazeGrid;

void Maze_InitCell(MazeCell* cell);
void Maze_InitGrid(MazeGrid* grid, int width, int height);
void Maze_FreeGrid(MazeGrid* grid);

int Maze_GetPosition(MazeGrid* grid, int position, enum Direction direction);
int Maze_HasNeighbor(MazeGrid* grid, int position, enum Direction direction);

int Maze_RemoveWall(MazeGrid* grid, int position, enum Direction direction);

#endif