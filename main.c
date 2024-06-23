#include <raylib.h>
#include "grid.h"

int main() {
	
	int gridWidth = 10;
	int gridHeight = 10;
	
	MazeGrid grid;
	Maze_InitGrid(&grid, gridWidth, gridHeight);
	
	grid.cells[5].bottom = OPEN;
	int downPos = Maze_GetPosition(&grid, 5, DOWN);
	grid.cells[downPos].top = OPEN;

	InitWindow(520, 520, "mazes");
	SetTargetFPS(60);
	
	int cell_size = 50;
	int x_start = 10;
	int y_start = 10;
	
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		int x = x_start; 
		int y = y_start;
		int position = 0;
		for (int row = 0; row < gridHeight; row++) {
			for (int column = 0; column < gridWidth; column++) {
				if (grid.cells[position].top == CLOSED) {
					DrawLine(x, y, x + cell_size, y, WHITE);
				}
				if (grid.cells[position].bottom == CLOSED) {
					DrawLine(x, y + cell_size, x + cell_size, y + cell_size, WHITE);
				}
				if (grid.cells[position].right == CLOSED) {
					DrawLine(x + cell_size, y, x + cell_size, y + cell_size, WHITE);
				}
				if (grid.cells[position].left == CLOSED) {
					DrawLine(x, y, x, y + cell_size, WHITE);
				}
				x += cell_size;
				position++;
			}
			x = x_start;
			y += cell_size;
		}
		
		EndDrawing();
	}
	
	Maze_FreeGrid(&grid);
	CloseWindow();
}