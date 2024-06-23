#include "grid.h"


void Maze_InitCell(MazeCell* cell) {
	cell->top = CLOSED;
	cell->right = CLOSED;
	cell->bottom = CLOSED;
	cell->left = CLOSED;
}

void Maze_InitGrid(MazeGrid* grid, int width, int height) {
	grid->cells = malloc(width * height * sizeof(MazeCell));
	grid->width = width;
	grid->height = height;
	int i = 0;
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			MazeCell cell;
			Maze_InitCell(&cell);
			grid->cells[i] = cell;
			i++;
		}
	}
}

int Maze_GetPosition(MazeGrid* grid, int position, enum Direction direction) {
	
	// error handling 
	// top row 
	if (position < grid->width && direction == UP) {
		return -1;
	}
	
	// bottom row 
	// right column 
	// left column 
	
	if (direction == UP) {
		return position - grid->width;
	}
	
	if (direction == RIGHT) {
		return position + 1; 
	}
	
	if (direction == DOWN) {
		return position + grid->width;
	}
	
	if (direction == LEFT) {
		return position - 1;
	}
	
	return -1;
}

void Maze_FreeGrid(MazeGrid* grid) {
	free(grid->cells);
}