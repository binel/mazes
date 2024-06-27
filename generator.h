#ifndef maze_generator_h
#define maze_generator_h

#include <stdlib.h>
#include <stdbool.h>

#include "grid.h" 

enum MazeType {
	BINARY_TREE,
	SIDEWINDER,
	RANDOM_WALK
};

typedef struct {
	int position;
	int maxPosition;
	bool finished; 
} BinaryTreeState;

typedef struct {
	int runLength;
	int position;
	int maxPosition;
	bool finished;
} SidewinderState;

typedef struct {
	int position;
	int unvisited;
	int maxPosition;
	bool finished;
} RandomWalkState;

void Maze_BinaryTree(MazeGrid* grid);
void Maze_BinaryTree_Process(MazeGrid* grid, BinaryTreeState* state);
void Maze_BinaryTree_InitState(MazeGrid* grid, BinaryTreeState* state);

void Maze_Sidewinder(MazeGrid* grid);
void Maze_Sidewinder_Process(MazeGrid* grid, SidewinderState* state);
void Maze_Sidewinder_InitState(MazeGrid* grid, SidewinderState* state);

void Maze_RandomWalk(MazeGrid* grid);
void Maze_RandomWalk_Process(MazeGrid* grid, RandomWalkState* state);
void Maze_RandomWalk_InitState( MazeGrid* grid, RandomWalkState* state);

#endif 