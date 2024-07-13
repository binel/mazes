#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "dijkstra.h"
#include "draw.h"
#include "generator.h"
#include "grid.h"
#include "memory.h"

static void ResizeDistanceGrid(MazeGrid* grid, DistanceGrid** distances) {
	Maze_FreeDistanceGrid(*distances);
	*distances = Maze_InitDistanceGrid(grid->width, grid->height);
}

int main() {
    srand(time(NULL));

    MazeGrid* grid = Maze_InitGrid(15, 15);

    DistanceGrid *distances = Maze_InitDistanceGrid(15, 15);
    DistanceCalculationState *state =
        Maze_InitDistanceCalculationState(grid, 0);

    int padding = 10;
    int windowHeight = 500;
    int windowWidth = 500;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWidth + (padding * 2), windowHeight + (padding * 2),
               "mazes");
    SetTargetFPS(10);

    DrawOptions options;
    options.xstart = padding;
    options.ystart = padding;
    options.height = windowHeight;
    options.width = windowWidth;
    options.wallWidth = 1;

    bool creatingGrid = false;
    bool coloringGrid = false;
    bool mazeColored = false;
    BinaryTreeState binaryTreeState;
    SidewinderState sidewinderState;
    RandomWalkState randomWalkState;
    enum MazeType maze;

    while (!WindowShouldClose()) {

        if (IsWindowResized()) {
            windowHeight = GetScreenHeight();
            windowWidth = GetScreenWidth();
            options.height = windowHeight;
            options.width = windowWidth;
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_UP)) {
            grid = Maze_IncreaseGridHeight(grid);
            distances = Maze_ResizeDistanceGrid(distances, grid);
            mazeColored = false;
        } else if (IsKeyPressed(KEY_UP)) {
            Maze_MovePlayerInDirection(grid, UP);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_DOWN)) {
            grid = Maze_DecreaseGridHeight(grid);
            distances = Maze_ResizeDistanceGrid(distances, grid);
            mazeColored = false;
        } else if (IsKeyPressed(KEY_DOWN)) {
            Maze_MovePlayerInDirection(grid, DOWN);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_RIGHT)) {
            grid = Maze_IncreaseGridWidth(grid);
            distances = Maze_ResizeDistanceGrid(distances, grid);
            mazeColored = false;
        } else if (IsKeyPressed(KEY_RIGHT)) {
            Maze_MovePlayerInDirection(grid, RIGHT);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_LEFT)) {
            grid = Maze_DecreaseGridWidth(grid);
            distances = Maze_ResizeDistanceGrid(distances, grid);
            mazeColored = false;
        } else if (IsKeyPressed(KEY_LEFT)) {
            Maze_MovePlayerInDirection(grid, LEFT);
        }

        if (IsKeyPressed(KEY_SPACE)) {
        	Maze_ResetGrid(grid);
			Maze_ResetDistanceGrid(distances);
            mazeColored = false;
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_B)) {
            creatingGrid = true;
            maze = BINARY_TREE;
            Maze_ResetGrid(grid);
            Maze_BinaryTree_InitState(grid, &binaryTreeState);
        } else if (IsKeyPressed(KEY_B)) {
            Maze_BinaryTree(grid);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_S)) {
            creatingGrid = true;
            maze = SIDEWINDER;
            Maze_ResetGrid(grid);
            Maze_Sidewinder_InitState(grid, &sidewinderState);
        } else if (IsKeyPressed(KEY_S)) {
            Maze_Sidewinder(grid);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_R)) {
            creatingGrid = true;
            maze = RANDOM_WALK;
            Maze_ResetGrid(grid);
            Maze_RandomWalk_InitState(grid, &randomWalkState);
        } else if (IsKeyPressed(KEY_R)) {
            Maze_RandomWalk(grid);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_C)) {
            coloringGrid = true;
            mazeColored = true;
            state =
                Maze_InitDistanceCalculationState(grid, grid->playerPosition);
        } else if (IsKeyPressed(KEY_C)) {
            distances = Maze_CalculateDistances(grid, grid->playerPosition);
            mazeColored = true;
        }

        if (IsKeyPressed(KEY_P)) {
            grid->playerEnabled = !grid->playerEnabled;
        }

        if (IsKeyPressed(KEY_ONE)) {
            options.wallWidth++;
        }

        if (IsKeyPressed(KEY_TWO)) {
            options.wallWidth--;
        }

        if (creatingGrid) {
            switch (maze) {
            case BINARY_TREE:
                Maze_BinaryTree_Process(grid, &binaryTreeState);
                if (binaryTreeState.finished) {
                    creatingGrid = false;
                }
                break;
            case SIDEWINDER:
                Maze_Sidewinder_Process(grid, &sidewinderState);
                if (sidewinderState.finished) {
                    creatingGrid = false;
                }
            case RANDOM_WALK:
                Maze_RandomWalk_Process(grid, &randomWalkState);
                if (randomWalkState.finished) {
                    creatingGrid = false;
                }
            default:
                break;
            }
        }

        if (coloringGrid) {
            Maze_CalculateDistances_Process(grid, distances, state);
            if (state->complete) {
                coloringGrid = false;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (mazeColored) {
            Maze_ColorMaze(grid, distances, &options);
        }

        Maze_DrawGrid(grid, &options);

        EndDrawing();
    }

    Maze_FreeGrid(grid);
    CloseWindow();
}