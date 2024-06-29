#include "draw.h"

void Maze_DrawGrid(MazeGrid* grid, int xstart, int ystart, int width, int height) {
	int cell_determinant = grid->width < grid->height ? grid->height : grid->width;
	int cell_size = (int)((double)width / (double)cell_determinant);
	int half_cell_size = (int)((double)cell_size / 2.0);
	int x = xstart; 
	int y = ystart;
	int position = 0;
	for (int row = 0; row < grid->height; row++) {
		for (int column = 0; column < grid->width; column++) {
			if (grid->cells[position].top == CLOSED) {
				DrawLine(x, y, x + cell_size, y, WHITE);
			}
			if (grid->cells[position].bottom == CLOSED) {
				DrawLine(x, y + cell_size, x + cell_size, y + cell_size, WHITE);
			}
			if (grid->cells[position].right == CLOSED) {
				DrawLine(x + cell_size, y, x + cell_size, y + cell_size, WHITE);
			}
			if (grid->cells[position].left == CLOSED) {
				DrawLine(x, y, x, y + cell_size, WHITE);
			}
			
			if (grid->playerEnabled && grid->playerPosition == position) {
				DrawCircle(x + half_cell_size, y + half_cell_size, half_cell_size, RED);
			}
			x += cell_size;
			position++;
		}
		x = xstart;
		y += cell_size;
	}
}