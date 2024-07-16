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

void Maze_Color_Now(MazeGrid *grid, DistanceGrid *distances);

void Maze_Color_Next_Step(MazeGrid *grid, DistanceGrid *distances);

void Maze_Color_SetColoring(MazeGrid *grid);

void Maze_Generate_Now(MazeGrid *grid, enum MazeType type);

void Maze_Generate_SetType(MazeGrid *grid, enum MazeType type);

bool Maze_Generate_Next_Step(MazeGrid *grid);

#endif