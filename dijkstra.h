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
} DistanceGrid;


/*
 * Encapsulates the state needed while calculating a distance grid. Used to 
 * handle animating the coloring of the grid
 */
typedef struct {
	int * frontier; 
	int * newFrontier; 
	int frontierIndex; 
	int distance; 
} DistanceCalculationState;

} Distance
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

DistanceGrid *Maze_CalculateDistances_Process(MazeGrid *grid, 
#endif