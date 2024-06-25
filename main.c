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

	InitWindow(520, 520, "mazes");
	SetTargetFPS(30);
	Maze_Sidewinder(&grid);
	
	while(!WindowShouldClose()) {
	
		if (IsKeyPressed(KEY_UP)) {
			Maze_MovePlayerInDirection(&grid, UP);
		}
		
		if (IsKeyPressed(KEY_DOWN)) {
			Maze_MovePlayerInDirection(&grid, DOWN);
		}
		
		if (IsKeyPressed(KEY_RIGHT)) {
			Maze_MovePlayerInDirection(&grid, RIGHT);
		}
		
		if (IsKeyPressed(KEY_LEFT)) {
			Maze_MovePlayerInDirection(&grid, LEFT);
		}	
		
		BeginDrawing();
		ClearBackground(BLACK);

		Maze_DrawGrid(&grid, 10, 10, 500, 500);
		
		EndDrawing();
	}
	
	Maze_FreeGrid(&grid);
	CloseWindow();
}