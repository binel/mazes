#include <stdlib.h>
#include <time.h>
#include <raylib.h>
#include "grid.h"
#include "draw.h" 
#include "generator.h"

int main() {
	srand(time(NULL));
	
	int gridWidth = 15;
	int gridHeight = 15;
	
	MazeGrid grid;
	Maze_InitGrid(&grid, gridWidth, gridHeight);
	
	//Maze_BinaryTree(&grid);
	//Maze_Sidewinder(&grid);

	InitWindow(520, 520, "mazes");
	SetTargetFPS(15);
	int step = 0; 
	SidewinderState state;
	state.position = 0;
	state.runLength = 0;
	while(!WindowShouldClose()) {
		if (step < gridWidth * gridHeight) {
			Maze_Sidewinder_Process(&grid, &state);
			step++;
			state.position = step;
		}
		if (step == gridWidth * gridHeight) {
			gridWidth = (rand() % 18) + 2;
			gridHeight = gridWidth;
			Maze_InitGrid(&grid, gridWidth, gridHeight);
			step = 0;
			state.position=step;
		}
		
		BeginDrawing();
		ClearBackground(BLACK);

		Maze_DrawGrid(&grid, 10, 10, 500, 500);
		
		EndDrawing();
	}
	
	Maze_FreeGrid(&grid);
	CloseWindow();
}