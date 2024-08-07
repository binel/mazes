#ifndef maze_binaryTree_h
#define maze_binaryTree_h

#include <stdbool.h>
#include <stdlib.h>

#include "generator.h"
#include "grid.h"

/*
 * Generates a maze using the Binary Tree algorithm. This generates a maze in
 * O(n) time, but the maze has significant limitations. It has a very noticeable
 * diagonal character, and two sides of the maze will always have completely
 * open corridors. In this implementation it is the bottom and right walls. Here
 * is an example maze:
 *
 * +---+---+---+---+---+
 * |       |       |   |
 * +---+   +---+   +   +
 * |       |       |   |
 * +---+   +---+   +   +
 * |   |   |   |       |
 * +   +   +   +---+   +
 * |   |       |       |
 * +   +---+   +---+   +
 * |                   |
 * +---+---+---+---+---+
 *
 */
void Maze_BinaryTree(MazeGrid *grid);

/*
 * Generates a binary tree maze step-by-step. Each call to this function will
 * complete one additional step of the maze generation process. This is useful
 * for animating the maze generation process
 */
bool Maze_BinaryTree_Process(MazeGrid *grid);
 
/*
 * Resets the generation state - call this prior to calling Maze_BinaryTree_Process 
 * for a new maze.
 */
void Maze_BinaryTree_Reset(MazeGrid *grid);

#endif
