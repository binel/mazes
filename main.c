#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include "grid.h"
#include "draw.h" 
#include "generator.h"

int main() {
	srand(time(NULL));
	
	int gridWidth = 10;
	int gridHeight = 10;
	
	MazeGrid grid;
	Maze_InitGrid(&grid, gridWidth, gridHeight);
	
	Maze_BinaryTree(&grid);
	

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