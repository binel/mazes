#include "input.h"

#include <raylib.h>

enum Command Maze_GetCommand() {
	if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_UP)) {
		return INCREASE_MAZE_HEIGHT;
	}
	
	if (IsKeyPressed(KEY_UP)) {
		return MOVE_PLAYER_UP;
	}

	if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_DOWN)) {
		return DECREASE_MAZE_HEIGHT;
	}
	
	if (IsKeyPressed(KEY_DOWN)) {
		return MOVE_PLAYER_DOWN;
	}

	if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_RIGHT)) {
		return INCREASE_MAZE_WIDTH;
	}
	if (IsKeyPressed(KEY_RIGHT)) {
		return MOVE_PLAYER_RIGHT;
	}

	if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_LEFT)) {
		return DECREASE_MAZE_WIDTH;
	}
	
	if (IsKeyPressed(KEY_LEFT)) {
		return MOVE_PLAYER_LEFT;
	}

	if (IsKeyPressed(KEY_SPACE)) {
		return RESET_MAZE;
	}

	if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_B)) {
		return GENERATE_BINARY_TREE;
	}
	
	if (IsKeyPressed(KEY_B)) {
		return GENERATE_BINARY_TREE_INSTANT;
	}

	if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_S)) {
		return GENERATE_SIDEWINDER;
	}
	if (IsKeyPressed(KEY_S)) {
		return GENERATE_SIDEWINDER_INSTANT;
	}

	if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_R)) {
		return GENERATE_RANDOM_WALK;
	}
	if (IsKeyPressed(KEY_R)) {
		return GENERATE_RANDOM_WALK_INSTANT;
	}

	if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_C)) {
		return COLOR_GRID;
	}
	if (IsKeyPressed(KEY_C)) {
		return COLOR_GRID_INSTANT;
	}	
	
	if (IsKeyPressed(KEY_P)) {
		return TOGGLE_PLAYER_STATE;
	}
	
	if (IsKeyPressed(KEY_G)) {
		return SET_GOALS_RANDOM;
	}
	
	return COMMAND_NONE;
}