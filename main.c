#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include "grid.h"
#include "draw.h" 
#include "generator.h"

int main() {
	srand(time(NULL));
	
	int gridWidth = 50;
	int gridHeight = 50;
	
	MazeGrid grid;
	Maze_InitGrid(&grid, gridWidth, gridHeight);
	
	//Maze_BinaryTree(&grid);
	//Maze_Sidewinder(&grid);

	InitWindow(520, 520, "mazes");
	SetTargetFPS(30);
	int step = 0; 
	while(!WindowShouldClose()) {
		if (step < gridWidth * gridHeight) {
			Maze_BinaryTree_Process(&grid, step);
			step++;
		}
		if (step == gridWidth * gridHeight) {
			gridWidth = (rand() % 18) + 2;
			gridHeight = gridWidth;
			Maze_InitGrid(&grid, gridWidth, gridHeight);
			step = 0;
		}
		BeginDrawing();
		ClearBackground(BLACK);

		Maze_DrawGrid(&grid, 10, 10, 500, 500);
		
		EndDrawing();
	}
	
	Maze_FreeGrid(&grid);
	CloseWindow();
}