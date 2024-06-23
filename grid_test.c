#include <stdio.h>

#include "grid.h"

int test_maze_get_position() {
	MazeGrid grid;
	Maze_InitGrid(&grid, 5, 5);
	
	// Top left corner cases 
	int position = Maze_GetPosition(&grid, 0, UP);
	if (position != -1) {
		printf("top left corner -> up: expected %d, but was %d\n", -1, position);
		return -1;
	}
	
	position = Maze_GetPosition(&grid, 0, LEFT);
	if (position != -1) {
		printf("top left corner -> left: expected %d, but was %d\n", -1, position);
		return -1;
	}
	
	position = Maze_GetPosition(&grid, 0, DOWN);
	if (position != 5) {
		printf("top left corner -> down: expected %d, but was %d\n", 5, position);
		return -1;
	}
	
	position = Maze_GetPosition(&grid, 0, RIGHT);
	if (position != 1) {
		printf("top left corner -> right: expected %d, but was %d\n", 1, position);
		return -1;
	}
	
	// Top right corner cases 
	position = Maze_GetPosition(&grid, 4, UP);
	if (position != -1) {
		printf("top right corner -> up: expected %d, but was %d\n", -1, position);
		return -1;
	}
	
	position = Maze_GetPosition(&grid, 4, LEFT);
	if (position != 3) {
		printf("top right corner -> left: expected %d, but was %d\n", 3, position);
		return -1;
	}
	
	position = Maze_GetPosition(&grid, 4, DOWN);
	if (position != 9) {
		printf("top right corner -> down: expected %d, but was %d\n", 9, position);
		return -1;
	}
	
	position = Maze_GetPosition(&grid, 4, RIGHT);
	if (position != -1) {
		printf("top right corner -> right: expected %d, but was %d\n", -1, position);
		return -1;
	}
	
	// Bottom left corner cases 
	position = Maze_GetPosition(&grid, 20, UP);
	if (position != 15) {
		printf("bottom left corner -> up: expected %d, but was %d\n", 15, position);
		return -1;
	}
	
	position = Maze_GetPosition(&grid, 20, LEFT);
	if (position != -1) {
		printf("bottom left corner -> left: expected %d, but was %d\n", -1, position);
		return -1;
	}
	
	position = Maze_GetPosition(&grid, 20, DOWN);
	if (position != -1) {
		printf("bottom left corner -> down: expected %d, but was %d\n", -1, position);
		return -1;
	}
	
	position = Maze_GetPosition(&grid, 20, RIGHT);
	if (position != 21) {
		printf("bottom left corner -> right: expected %d, but was %d\n", 21, position);
		return -1;
	}
		
	// Bottom right corner cases 
		position = Maze_GetPosition(&grid, 24, UP);
	if (position != 19) {
		printf("bottom left corner -> up: expected %d, but was %d\n", 19, position);
		return -1;
	}
	
	position = Maze_GetPosition(&grid, 24, LEFT);
	if (position != 23) {
		printf("bottom left corner -> left: expected %d, but was %d\n", 23, position);
		return -1;
	}
	
	position = Maze_GetPosition(&grid, 24, DOWN);
	if (position != -1) {
		printf("bottom left corner -> down: expected %d, but was %d\n", -1, position);
		return -1;
	}
	
	position = Maze_GetPosition(&grid, 24, RIGHT);
	if (position != -1) {
		printf("bottom left corner -> right: expected %d, but was %d\n", -1, position);
		return -1;
	}
	
	return 0;
}

int main() {
	
	int test_result;
	int passed_count = 0;
	int failed_count = 0;
	
	printf("running test_maze_get_position\n");
	test_result = test_maze_get_position();
	if (test_result != 0) {
		printf("test_maze_get_position failed.");
		failed_count++;
	} else {
		passed_count++;
	}
	
	printf("Tests complete. %d passed, %d failed\n", passed_count, failed_count);
	
	return 0;
}