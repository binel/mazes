#include <raylib.h>
#include "grid.h"
#include "draw.h" 

int main() {
	
	int gridWidth = 10;
	int gridHeight = 10;
	
	MazeGrid grid;
	Maze_InitGrid(&grid, gridWidth, gridHeight);
	
	Maze_RemoveWall(&grid, 11, DOWN);
	Maze_RemoveWall(&grid, 11, UP);
	Maze_RemoveWall(&grid, 11, LEFT);
	Maze_RemoveWall(&grid, 11, RIGHT);
	
	Maze_RemoveWall(&grid, 0, UP);

	InitWindow(520, 520, "mazes");
	SetTargetFPS(60);
	
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);

		Maze_DrawGrid(&grid, 10, 10, 500, 500);
		
		EndDrawing();
	}
	
	Maze_FreeGrid(&grid);
	CloseWindow();
}