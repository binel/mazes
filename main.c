#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "draw.h"
#include "generator.h"
#include "grid.h"

int main() {
    srand(time(NULL));

    int gridWidth = 15;
    int gridHeight = 15;

    MazeGrid grid;
    Maze_InitGrid(&grid, gridWidth, gridHeight);

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

    bool creatingGrid = false;
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
            gridHeight++;
            Maze_InitGrid(&grid, gridWidth, gridHeight);
        } else if (IsKeyPressed(KEY_UP)) {
            Maze_MovePlayerInDirection(&grid, UP);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_DOWN)) {
            gridHeight--;
            Maze_InitGrid(&grid, gridWidth, gridHeight);
        } else if (IsKeyPressed(KEY_DOWN)) {
            Maze_MovePlayerInDirection(&grid, DOWN);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_RIGHT)) {
            gridWidth++;
            Maze_InitGrid(&grid, gridWidth, gridHeight);
        } else if (IsKeyPressed(KEY_RIGHT)) {
            Maze_MovePlayerInDirection(&grid, RIGHT);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_LEFT)) {
            gridWidth--;
            Maze_InitGrid(&grid, gridWidth, gridHeight);
        } else if (IsKeyPressed(KEY_LEFT)) {
            Maze_MovePlayerInDirection(&grid, LEFT);
        }

        if (IsKeyPressed(KEY_SPACE)) {
            Maze_InitGrid(&grid, gridWidth, gridHeight);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_B)) {
            creatingGrid = true;
            maze = BINARY_TREE;
            Maze_InitGrid(&grid, gridWidth, gridHeight);
            Maze_BinaryTree_InitState(&grid, &binaryTreeState);
        } else if (IsKeyPressed(KEY_B)) {
            Maze_BinaryTree(&grid);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_S)) {
            creatingGrid = true;
            maze = SIDEWINDER;
            Maze_InitGrid(&grid, gridWidth, gridHeight);
            Maze_Sidewinder_InitState(&grid, &sidewinderState);
        } else if (IsKeyPressed(KEY_S)) {
            Maze_Sidewinder(&grid);
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_R)) {
            creatingGrid = true;
            maze = RANDOM_WALK;
            Maze_InitGrid(&grid, gridWidth, gridHeight);
            Maze_RandomWalk_InitState(&grid, &randomWalkState);
            Maze_ResetVisitedState(&grid);
        } else if (IsKeyPressed(KEY_R)) {
            Maze_ResetVisitedState(&grid);
            Maze_RandomWalk(&grid);
        }

        if (IsKeyPressed(KEY_P)) {
            grid.playerEnabled = !grid.playerEnabled;
        }

        if (creatingGrid) {
            switch (maze) {
            case BINARY_TREE:
                Maze_BinaryTree_Process(&grid, &binaryTreeState);
                if (binaryTreeState.finished) {
                    creatingGrid = false;
                }
                break;
            case SIDEWINDER:
                Maze_Sidewinder_Process(&grid, &sidewinderState);
                if (sidewinderState.finished) {
                    creatingGrid = false;
                }
            case RANDOM_WALK:
                Maze_RandomWalk_Process(&grid, &randomWalkState);
                if (randomWalkState.finished) {
                    creatingGrid = false;
                }
            default:
                break;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        Maze_DrawGrid(&grid, &options);

        EndDrawing();
    }

    Maze_FreeGrid(&grid);
    CloseWindow();
}