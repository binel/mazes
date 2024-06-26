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

void Maze_Sidewinder(MazeGrid* grid) {
	SidewinderState state;
	Maze_Sidewinder_InitState(&state);
	
	while (state.position < (grid->width * grid->height) - 1) {
		Maze_Sidewinder_Process(grid, &state);
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
		Maze_RemoveWall(grid, state->position, RIGHT);
	}
	state->position++;
}

void Maze_Sidewinder_InitState(SidewinderState* state) {
	state->position = 0;
	state->runLength = 0; 	
}

void Maze_RandomWalk(MazeGrid* grid) {
	RandomWalkState state;
	Maze_RandomWalk_InitState(&state, grid);
	
	while(state.unvisited > 0) {
		Maze_RandomWalk_Process(grid, &state);
	}
}


void Maze_RandomWalk_Process(MazeGrid* grid, RandomWalkState* state) {
	int direction = rand() % 4;
	int newPosition;
	switch (direction) {
		case 0:
			newPosition = Maze_GetPosition(grid, state->position, UP);
			break;
		case 1:
			newPosition = Maze_GetPosition(grid, state->position, DOWN);
			break;
		case 2:
			newPosition = Maze_GetPosition(grid, state->position, LEFT);
			break;
		case 3:
			newPosition = Maze_GetPosition(grid, state->position, RIGHT);
			break;
	}
	
	if (newPosition == -1) {
		return;
	}
	
	if (Maze_IsPositionVisited(grid, newPosition)) {
		switch (direction) {
			case 0:
				Maze_RemoveWall(grid, state->position, UP);
				break;
			case 1:
				Maze_RemoveWall(grid, state->position, DOWN);
				break;
			case 2:
				Maze_RemoveWall(grid, state->position, LEFT);
				break;
			case 3:
				Maze_RemoveWall(grid, state->position, RIGHT);
				break;
		}	
		state->unvisited -= 1;
	}

	state->position = newPosition;
}

void Maze_RandomWalk_InitState(RandomWalkState* state, MazeGrid* grid) {
	state->position = rand() % (grid->width * grid->height);
	state->unvisited = (grid->width * grid->height) - 1;
}