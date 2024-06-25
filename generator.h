#ifndef maze_generator_h
#define maze_generator_h

#include <stdlib.h>

#include "grid.h" 

typedef struct {
	int runLength;
	int position;
} SidewinderState;

typedef struct {
	int position;
	int unvisited;
} RandomWalkState;

void Maze_BinaryTree(MazeGrid* grid);
void Maze_BinaryTree_Process(MazeGrid* grid, int step);

void Maze_Sidewinder(MazeGrid* grid);
void Maze_Sidewinder_Process(MazeGrid* grid, SidewinderState* state);

void Maze_RandomWalk(MazeGrid* grid);
void Maze_RandomWalk_Process(MazeGrid* grid, RandomWalkState* state);


#endif 