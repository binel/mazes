#ifndef maze_generator_h
#define maze_generator_h

#include <stdlib.h>

#include "grid.h" 

typedef struct {
	int runLength;
	int position;
} SidewinderState;

void Maze_BinaryTree(MazeGrid* grid);
void Maze_BinaryTree_Process(MazeGrid* grid, int step);

void Maze_Sidewinder(MazeGrid* grid);
void Maze_Sidewinder_Process(MazeGrid* grid, SidewinderState* state);

#endif 