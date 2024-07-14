#ifndef maze_randomWalk_h
#define maze_randomWalk_h

#include "grid.h"

/*
 * Generates a maze using a random walk. This is also called the
 * Aldous-Broder algorithm. It's very inefficient, but I actually don't know
 * what the time complexity is. But on the plus side it generates fully random
 * mazes. Here is an example:
 *
 * +---+---+---+---+---+
 * |           |       |
 * +   +---+   +---+   +
 * |   |   |       |   |
 * +---+   +   +---+   +
 * |   |       |   |   |
 * +   +---+   +   +   +
 * |                   |
 * +   +   +   +   +   +
 * |   |   |   |   |   |
 * +---+---+---+---+---+
 *
 *
 * @param grid - the grid to etch the maze into.
 */
void Maze_RandomWalk(MazeGrid *grid);

/*
 * Generates a random walk (Aldous-Broder) maze step-by-step. Each call to this
 * function will complete one additional step of the maze generation process.
 * This is useful for animating the maze generation process.
 *
 * @param grid - the grid to etch the maze into
 * @param state - the current state of the maze generation process.
 */
bool Maze_RandomWalk_Process(MazeGrid *grid);

/*
 * Initializes the RandomWalkState so it is ready to be used to generate a maze.
 *
 * @param grid - the grid that will be used for generation. It is not modified.
 * @param state - the state to initialize
 */
void Maze_RandomWalk_Reset(MazeGrid *grid);

#endif