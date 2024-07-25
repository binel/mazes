#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "dijkstra.h"
#include "draw.h"
#include "generator.h"
#include "grid.h"
#include "memory.h"
#include "command.h"
#include "input.h"

static MazeGrid *grid = NULL;
static DistanceGrid *distances = NULL;

static bool coloringGrid = false;

static void ResizeDistanceGrid(MazeGrid *grid, DistanceGrid **distances) {
    Maze_FreeDistanceGrid(*distances);
    *distances = Maze_InitDistanceGrid(grid->width, grid->height);
}

static void HandleInput() {
	enum Command command = Maze_GetCommand();
	
	switch (command) {
		case MOVE_PLAYER_UP:
			Maze_MovePlayerInDirection(grid, UP);
			break;
		case MOVE_PLAYER_DOWN:
			Maze_MovePlayerInDirection(grid, DOWN);
			break;
		case MOVE_PLAYER_LEFT:
			Maze_MovePlayerInDirection(grid, LEFT);
			break;
		case MOVE_PLAYER_RIGHT:
			Maze_MovePlayerInDirection(grid, RIGHT);
			break;
			
		case INCREASE_MAZE_HEIGHT:
			grid = Maze_IncreaseGridHeight(grid);
			distances = Maze_ResizeDistanceGrid(distances, grid);
			break;
		case INCREASE_MAZE_WIDTH:
			grid = Maze_IncreaseGridWidth(grid);
			distances = Maze_ResizeDistanceGrid(distances, grid);
			break;
		case DECREASE_MAZE_HEIGHT:
			grid = Maze_DecreaseGridHeight(grid);
			distances = Maze_ResizeDistanceGrid(distances, grid);
			break;
		case DECREASE_MAZE_WIDTH:
			grid = Maze_DecreaseGridWidth(grid);
			distances = Maze_ResizeDistanceGrid(distances, grid);
			break;
		
		case GENERATE_BINARY_TREE:
			Maze_Generate_SetType(grid, BINARY_TREE);
			break;
		case GENERATE_BINARY_TREE_INSTANT:
			Maze_Generate_Now(grid, BINARY_TREE);
			break;
			
		case GENERATE_SIDEWINDER:
			Maze_Generate_SetType(grid, SIDEWINDER);
			break;
		case GENERATE_SIDEWINDER_INSTANT:
			Maze_Generate_Now(grid, SIDEWINDER);
			break;
			
		case GENERATE_RANDOM_WALK:
			Maze_Generate_SetType(grid, RANDOM_WALK);
			break;
		case GENERATE_RANDOM_WALK_INSTANT:
			Maze_Generate_Now(grid, RANDOM_WALK);
			break;
			
		case COLOR_GRID:
			Maze_Color_SetColoring(grid);
			break;
			
		case COLOR_GRID_INSTANT:
			Maze_Color_Now(grid, distances);
			break;
		
			
		case RESET_MAZE:
			Maze_ResetGrid(grid);
			Maze_ResetDistanceGrid(distances);	
			break;
			
		case TOGGLE_PLAYER_STATE:
			grid->playerEnabled = !grid->playerEnabled;	
			
		case SET_GOALS_RANDOM:
			Maze_SetStartOfMaze_Random(grid);
			Maze_SetEndOfMaze_Random(grid);
			grid->playerPosition = grid->startingPosition;
					
		case COMMAND_NONE:
		default:
			break;
	}
}

int main() {
    srand(time(NULL));

    grid = Maze_InitGrid(15, 15);

    distances = Maze_InitDistanceGrid(15, 15);

    int padding = 10;
    int windowHeight = 500;
    int windowWidth = 500;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWidth + (padding * 2), windowHeight + (padding * 2),
               "mazes");
    SetTargetFPS(30);

    DrawOptions options;
    options.xstart = padding;
    options.ystart = padding;
    options.height = windowHeight;
    options.width = windowWidth;

    coloringGrid = false;

    while (!WindowShouldClose()) {

        if (IsWindowResized()) {
            windowHeight = GetScreenHeight();
            windowWidth = GetScreenWidth();
            options.height = windowHeight;
            options.width = windowWidth;
        }

		HandleInput();
		
        Maze_Generate_Next_Step(grid);
        Maze_Color_Next_Step(grid, distances);

        Maze_SetIfWon(grid);

        BeginDrawing();
        ClearBackground(BLACK);

        Maze_ColorMaze(grid, distances, &options);
        Maze_DrawGrid(grid, &options);

        EndDrawing();
    }

    Maze_FreeGrid(grid);
    CloseWindow();
}
