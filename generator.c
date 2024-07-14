#include "generator.h"
#include "binaryTree.h"
#include "sidewinder.h"
#include "randomWalk.h"

static enum MazeType _currentMaze = NONE;

static bool _currentlyGenerating = false;

void Maze_Generate_Now(MazeGrid *grid, enum MazeType type) {
	switch (type) {
		case BINARY_TREE:
			Maze_BinaryTree(grid);
			break;
		case SIDEWINDER: 
			Maze_Sidewinder(grid);
			break;
		case RANDOM_WALK:
			Maze_RandomWalk(grid);
			break;
		default:
			break;
	}
}

void Maze_Generate_SetType(MazeGrid *grid, enum MazeType type) {
	Maze_RandomWalk_Reset(grid);
	Maze_BinaryTree_Reset(grid);
	Maze_Sidewinder_Reset(grid);
	Maze_ResetGrid(grid);
	_currentMaze = type;
	_currentlyGenerating = true;
}

bool Maze_Generate_Next_Step(MazeGrid *grid) {
	if (!_currentlyGenerating) {
		return false;
	}

	switch (_currentMaze) {
		case BINARY_TREE:
			if (Maze_BinaryTree_Process(grid)) {
				_currentlyGenerating = false;
			}
			break;
		case SIDEWINDER:
			if (Maze_Sidewinder_Process(grid)) {
				_currentlyGenerating = false;
			}
			break;
		case RANDOM_WALK:
			if (Maze_RandomWalk_Process(grid)) {
				_currentlyGenerating = false;
			}
			break;
		default:
			break;
	}
	
	return _currentlyGenerating;
}


