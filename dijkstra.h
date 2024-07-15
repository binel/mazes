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
 *
 * @param width - the width of the grid in cells
 * @param height - the height of the grid in cells
 *
 */
DistanceGrid *Maze_InitDistanceGrid(int width, int height);

/*
 * Frees the given distance grid
 *
 * @param grid - the grid to free
 */
void Maze_FreeDistanceGrid(DistanceGrid *grid);

DistanceGrid *Maze_ResizeDistanceGrid(DistanceGrid *grid, MazeGrid *mazeGrid);

void Maze_ResetDistanceGrid(DistanceGrid *grid);

/*
 * Calculates the distance of each cell in the maze grid from the provided
 * starting position
 *
 * @param grid - the grid we are working with. Is not modified
 * @param startingPosition - the position in the grid to calculate distance
 * from. in the resulting distance grid, this position will have distance 0.
 *
 */
DistanceGrid *Maze_CalculateDistances(MazeGrid *grid, int startingPosition);

/*
 * Initializes a DistanceCalculationState so it is ready to be used by
 * Maze_CalculateDistances_Process
 *
 * @param grid - the grid that we want to calculate distances in
 * @param startingPosition - the position in the grid that we should start
 * calculating distances from, this position will have distance 0.
 */
void Maze_CalculateDistances_Reset(MazeGrid *grid, int startingPosition);

/*
 * Generates a binary tree maze step-by-step. Each call to this function will
 * complete one additional step of the maze generation process. This is useful
 * for animating the maze generation process
 *
 * @param grid - the grid we are working with. It is not modified.
 * @param distanceGrid - the distance grid we are creating. Modified.
 * @param state - the current state of the distance calculation process.
 */
bool Maze_CalculateDistances_Process(MazeGrid *grid, DistanceGrid *distanceGrid);
#endif