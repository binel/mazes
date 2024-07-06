/*
 * generator.h
 *
 * This file contains all the logic related to generating mazes.
 *
 */

#ifndef maze_generator_h
#define maze_generator_h

#include <stdbool.h>
#include <stdlib.h>

#include "grid.h"

/*
 * Each of the different kinds of mazes we are capable of producing
 */
enum MazeType { BINARY_TREE, SIDEWINDER, RANDOM_WALK };

/*
 * Holds the state required to generate a binary tree maze.
 */
typedef struct {
    int position;    // the current position in the maze
    int maxPosition; // the index of the last cell in the maze
    bool finished;   // True if generation is complete
} BinaryTreeState;

/*
 * Holds the state required to generate a sidewinder maze
 */
typedef struct {
    int runLength;   // the length of the current "run"
    int position;    // the current position in the maze
    int maxPosition; // the index of the last cell in the maze
    bool finished;   // True if generation is complete
} SidewinderState;

/*
 * Holds the state required to generate a random walk maze.
 */
typedef struct {
    int position;    // the current position of the walker in the maze
    int unvisited;   // the count of cells that haven't yet been visited
    int maxPosition; // the index of the last cell of the maze
    bool finished;   // True if the generation is complete
} RandomWalkState;

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
 * @param grid The maze grid to etch the maze into.
 */
void Maze_BinaryTree(MazeGrid *grid);

/*
 * Generates a binary tree maze step-by-step. Each call to this function will
 * complete one additional step of the maze generation process. This is useful
 * for animating the maze generation process
 *
 * @param grid - the grid to etch the maze into.
 * @param state - the current state of the generation process.
 */
void Maze_BinaryTree_Process(MazeGrid *grid, BinaryTreeState *state);

/*
 * Initializes the BinaryTreeState so it is ready to be used to generate a maze.
 *
 * @param grid - the grid that will be used for generation. It is not modified
 * @param state - the state to initialize
 */
void Maze_BinaryTree_InitState(MazeGrid *grid, BinaryTreeState *state);

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
void Maze_Sidewinder_Process(MazeGrid *grid, SidewinderState *state);

/*
 * Initializes the SidewinderState so it is ready to be used to generate a maze.
 *
 * @param grid - the grid that will be used for generation. It is not modified.
 * @param state - the state to initialize
 */
void Maze_Sidewinder_InitState(MazeGrid *grid, SidewinderState *state);

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
void Maze_RandomWalk_Process(MazeGrid *grid, RandomWalkState *state);

/*
 * Initializes the RandomWalkState so it is ready to be used to generate a maze.
 *
 * @param grid - the grid that will be used for generation. It is not modified.
 * @param state - the state to initialize
 */
void Maze_RandomWalk_InitState(MazeGrid *grid, RandomWalkState *state);

#endif