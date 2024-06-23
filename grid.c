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
	if (position > grid->width * (grid->height - 1) - 1 && direction == DOWN) {
		return -1;
	}
	
	// right column 
	if (position != 0 && (position + 1) % grid->width == 0 && direction == RIGHT) {
		return -1;
	}
	// left column 
	if (position % grid->width == 0 && direction == LEFT) {
		return -1;
	}
	
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

int Maze_RemoveWall(MazeGrid* grid, int position, enum Direction direction) {
	if (position < 0 || position > grid->width * grid->height) {
		return -1;
	}

	int neighborPosition = Maze_GetPosition(grid, position, direction);
	if (neighborPosition == -1) {
		// Just update the single cell - useful for opening exits and entrances 
		switch (direction) {
			case UP: 
				grid->cells[position].top = OPEN;
				break;
			case DOWN: 
				grid->cells[position].bottom = OPEN;
				break;
			case LEFT: 
				grid->cells[position].left = OPEN;
				break;
			case RIGHT: 
				grid->cells[position].right = OPEN;
				break;
		}		
	}
	
	switch (direction) {
		case UP: 
			grid->cells[position].top = OPEN;
			grid->cells[neighborPosition].bottom = OPEN;
			break;
		case DOWN: 
			grid->cells[position].bottom = OPEN;
			grid->cells[neighborPosition].top = OPEN;
			break;
		case LEFT: 
			grid->cells[position].left = OPEN;
			grid->cells[neighborPosition].right = OPEN;
			break;
		case RIGHT: 
			grid->cells[position].right = OPEN;
			grid->cells[neighborPosition].left = OPEN;
			break;
	}
	
	return 0;
}

void Maze_FreeGrid(MazeGrid* grid) {
	free(grid->cells);
}