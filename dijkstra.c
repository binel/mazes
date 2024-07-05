#include "dijkstra.h"

#include <stdlib.h>

DistanceGrid* Maze_InitDistanceGrid(int width, int height ) {
	DistanceGrid* grid = (DistanceGrid *)malloc(sizeof(DistanceGrid));
	grid->distances = (int *)malloc(width * height * sizeof(int));
	return grid;
}

void Maze_FreeDistanceGrid(DistanceGrid *grid) {
	free(grid->distances);
}

DistanceGrid* Maze_CalculateDistances(MazeGrid *grid, int startingPosition) {
	DistanceGrid* distanceGrid = Maze_InitDistanceGrid(grid->width, grid->height);
	return distanceGrid;
}