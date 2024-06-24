#include "generator.h"

void Maze_BinaryTree(MazeGrid* grid) {
	int position = 0;
	for (int column = 0; column < grid->width; column++) {
		for (int row = 0; row < grid->height; row++) {
			// if there is a down and right neighbor, randomly pick one to open 
			int hasDown = Maze_HasNeighbor(grid, position, DOWN) == 0;
			int hasRight = Maze_HasNeighbor(grid, position, RIGHT) == 0;
			if (hasDown && hasRight) {
				if (rand() % 2 == 0) {
					Maze_RemoveWall(grid, position, DOWN);
				} else {
					Maze_RemoveWall(grid, position, RIGHT);
				}
			}
			// if only south or east, open that one 
			else if (hasDown) {
				Maze_RemoveWall(grid, position, DOWN);	
			}
			else if (hasRight) {
				Maze_RemoveWall(grid, position, RIGHT);
			}
			// otherwise do nothing 
			position++;
		}
	}
}