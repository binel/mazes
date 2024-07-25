#ifndef maze_dijkstra_h
#define maze_dijkstra_h

#include "grid.h"

/*
 * Encapsulates the distance of each cell in the grid from a given cell
 */
typedef struct {
    // width of the grid in cells
    int width;
    // height of the grid in cells
    int height;
    // the maximum distance from the starting cell
    int maxDistance;
    // an array width * height in size, that describes the distance from the
    // starting position.
    int *distances;
    // Once any distances have been calculated, this will be set to true
    bool calculated;
} DistanceGrid;

/*
 * Initializes a given distance grid for with the provided width and height
 */
DistanceGrid *Maze_InitDistanceGrid(int width, int height);

/*
 * Frees the given distance grid
 */
void Maze_FreeDistanceGrid(DistanceGrid *grid);

/*
 * Resizes the given distance grid so that it is the same size as the 
 * provided mazeGrid
 */
DistanceGrid *Maze_ResizeDistanceGrid(DistanceGrid *grid, MazeGrid *mazeGrid);

/*
 * Resets the distance grid so that each cell has a distance of -1 
 */
void Maze_ResetDistanceGrid(DistanceGrid *grid);

/*
 * Calculates the distance of each cell in the maze grid from the provided
 * starting position
 */
void Maze_CalculateDistances(MazeGrid *grid, int startingPosition, DistanceGrid *distanceGrid);

/*
 * Initializes a DistanceCalculationState so it is ready to be used by
 * Maze_CalculateDistances_Process
 */
void Maze_CalculateDistances_Reset(MazeGrid *grid, int startingPosition);

/*
 * Generates a binary tree maze step-by-step. Each call to this function will
 * complete one additional step of the maze generation process. This is useful
 * for animating the maze generation process
 */
bool Maze_CalculateDistances_Process(MazeGrid *grid, DistanceGrid *distanceGrid);
#endif
