#ifndef maze_sidewinder_h
#define maze_sidewinder_h

#include "grid.h"

/*
 * Generates a maze using the sidewinder algorithm. This generates a maze in
 * O(n) time. This maze is similar to Binary Tree mazes, but only a single side
 * of the maze have completely open corridors - in this implementation the
 * bottom. Here is an example:
 *
 * +---+---+---+---+---+
 * |       |       |   |
 * +---+   +---+   +   +
 * |   |   |   |   |   |
 * +   +   +   +   +   +
 * |                   |
 * +---+---+   +---+---+
 * |   |   |   |       |
 * +   +   +   +   +---+
 * |                   |
 * +---+---+---+---+---+
 *
 * @param grid The maze grid to etch the maze into.
 */
void Maze_Sidewinder(MazeGrid *grid);

/*
 * Generates a sidewinder maze step-by-step. Each call to this function will
 * complete one additional step of the maze generation process. This is useful
 * for animating the maze generation process.
 *
 * @param grid - the grid to etch the maze into.
 * @param state - the current state of the maze generation process.
 */
bool Maze_Sidewinder_Process(MazeGrid *grid);

void Maze_Sidewinder_Reset(MazeGrid *grid);

#endif