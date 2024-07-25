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
#include "dijkstra.h"

/*
 * Each of the different kinds of mazes we are capable of producing
 */
enum MazeType { NONE, BINARY_TREE, SIDEWINDER, RANDOM_WALK };

/*
 * Color the grid (calculate distances) instantly
 */
void Maze_Color_Now(MazeGrid *grid, DistanceGrid *distances);

/*
 * Complete the next step in coloring (calculating distnaces) for the 
 * grid. 
 */
void Maze_Color_Next_Step(MazeGrid *grid, DistanceGrid *distances);

/*
 * Indicate that we are currently coloring the grid. This ensures 
 * that subsequent calls to Maze_Color_Next_Step will actually 
 * complete the next step. 
 */
void Maze_Color_SetColoring(MazeGrid *grid);

/*
 * Etch the provided type of maze into the provided maze grid instantly. 
 */
void Maze_Generate_Now(MazeGrid *grid, enum MazeType type);

/*
 * Indicate that we are currently generating a maze of the provided type. 
 * This ensures that subsequent calls to Maze_Generate_Next_Step will 
 * actually complete the next step 
 */
void Maze_Generate_SetType(MazeGrid *grid, enum MazeType type);

/*
 * Complete the next step in etching the maze into the grid
 */
bool Maze_Generate_Next_Step(MazeGrid *grid);

#endif
