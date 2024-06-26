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

		if (IsKeyPressed(KEY_SPACE)) {
			Maze_InitGrid(&grid, gridWidth, gridHeight);
		}

		if (IsKeyPressed(KEY_B)) {
			Maze_BinaryTree(&grid);
		}
		
		if (IsKeyPressed(KEY_S)) {
			Maze_Sidewinder(&grid);
		}
		
		if (IsKeyPressed(KEY_R)) {
			Maze_RandomWalk(&grid);
		}
		
		BeginDrawing();
		ClearBackground(BLACK);

		Maze_DrawGrid(&grid, 10, 10, 500, 500);
		
		EndDrawing();
	}
	
	Maze_FreeGrid(&grid);
	CloseWindow();
}