#include "generator.h"

void Maze_BinaryTree(MazeGrid* grid) {
	int position = 0;
	for (int column = 0; column < grid->width; column++) {
		for (int row = 0; row < grid->height; row++) {
			Maze_BinaryTree_Process(grid, position);
			position++;
		}
	}
}

void Maze_BinaryTree_Process(MazeGrid* grid, int step) {
	// if there is a down and right neighbor, randomly pick one to open 
	int hasDown = Maze_HasNeighbor(grid, step, DOWN);
	int hasRight = Maze_HasNeighbor(grid, step, RIGHT);
	if (hasDown && hasRight) {
		if (rand() % 2 == 0) {
			Maze_RemoveWall(grid, step, DOWN);
		} else {
			Maze_RemoveWall(grid, step, RIGHT);
		}
	}
	// if only south or east, open that one 
	else if (hasDown) {
		Maze_RemoveWall(grid, step, DOWN);	
	}
	else if (hasRight) {
		Maze_RemoveWall(grid, step, RIGHT);
	}
}

// todo doesn't work correctly yet 
void Maze_Sidewinder(MazeGrid* grid) {
	SidewinderState state;
	state.position = 0;
	state.runLength = 0; 
	
	for (int column = 0; column < grid->width; column++) {
		for (int row = 0; row < grid->height; row++) {
			Maze_Sidewinder_Process(grid, &state);
			state.position++;
		}
	}
}

void Maze_Sidewinder_Process(MazeGrid* grid, SidewinderState* state) {
	int hasDown = Maze_HasNeighbor(grid, state->position, DOWN);
	int hasRight = Maze_HasNeighbor(grid, state->position, RIGHT);
	state->runLength++;
	// should end run 
	if (!hasRight || (hasDown && rand() % 2 == 0)) {
		int openDownPos = state->position - (rand() % state->runLength);
		Maze_RemoveWall(grid, openDownPos, DOWN);
		
		state->runLength = 0;
	}	
	else {
		//state->runLength++;
		Maze_RemoveWall(grid, state->position, RIGHT);
	}	
}