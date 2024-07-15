#include "dijkstra.h"
#include "memory.h"

#include <stdlib.h>

static int *_frontier = NULL;
static int *_newFrontier = NULL;
static int _frontierIndex; 
static int _newFrontierIndex; 
static int _distance;
static bool _complete; 

DistanceGrid *Maze_InitDistanceGrid(int width, int height) {
    DistanceGrid *grid = (DistanceGrid *)Maze_malloc(sizeof(DistanceGrid));
    grid->width = width;
    grid->height = height;
    grid->maxDistance = -1;
    grid->calculated = false;
    grid->distances = (int *)Maze_malloc(width * height * sizeof(int));
    for (int i = 0; i < width * height; i++) {
        grid->distances[i] = -1;
    }
    return grid;
}

void Maze_FreeDistanceGrid(DistanceGrid *grid) {
    Maze_free(grid->distances);
    Maze_free(grid);
}

DistanceGrid *Maze_ResizeDistanceGrid(DistanceGrid *grid, MazeGrid *mazeGrid) {
    Maze_FreeDistanceGrid(grid);
    return Maze_InitDistanceGrid(mazeGrid->width, mazeGrid->height);
}

void Maze_ResetDistanceGrid(DistanceGrid *grid) {
    grid->calculated = false;
    for (int i = 0; i < grid->width * grid->height; i++) {
        grid->distances[i] = -1;
    }
}

DistanceGrid *Maze_CalculateDistances(MazeGrid *grid, int startingPosition) {
    DistanceGrid *distanceGrid =
        Maze_InitDistanceGrid(grid->width, grid->height);

    Maze_CalculateDistances_Reset(grid, startingPosition);

    while (!_complete) {
        Maze_CalculateDistances_Process(grid, distanceGrid);
    }
    distanceGrid->calculated = true;
    return distanceGrid;
}

void Maze_CalculateDistances_Reset(MazeGrid *grid, int startingPosition) {
	if (_frontier != NULL) {
		Maze_free(_frontier);
	}
	
	if (_newFrontier != NULL) {
		Maze_free(_newFrontier);
	}
	
    // horrible - do a dynamic array later
    _frontier = Maze_malloc(grid->width * grid->height * sizeof(int));
    _newFrontier = Maze_malloc(grid->width * grid->height * sizeof(int));
    for (int i = 0; i < grid->width * grid->height; i++) {
        _frontier[i] = -1;
        _newFrontier[i] = -1;
    }

    _distance = 0;
    _frontierIndex = 0;
    _newFrontierIndex = -1;
    _frontier[0] = startingPosition;
    _complete = false;
}

bool Maze_CalculateDistances_Process(MazeGrid *grid, DistanceGrid *distanceGrid) {
    // TODO some of the ugliest code I've ever written in here, must be a better
    // way

    if (_complete) {
        return true;
    }

    if (!distanceGrid->calculated) {
        distanceGrid->calculated = true;
    }

    if (_frontierIndex == -1) {
        // if there is nothing in the new frontier, we are done
        if (_newFrontierIndex == -1) {
            _complete = true;
            return true;
        }

        // move newFrontier to be frontier
        for (int i = 0; i <= _newFrontierIndex; i++) {
            _frontier[i] = _newFrontier[i];
        }
        _frontierIndex = _newFrontierIndex;
        _newFrontierIndex = -1;
        _distance++;
        distanceGrid->maxDistance = _distance;
    }

    int position = _frontier[_frontierIndex];
    distanceGrid->distances[position] = _distance;
    _frontierIndex -= 1;
    // add connected cells to the new Frontier

    MazeCell cell = grid->cells[position];
    int upIndex = Maze_GetPosition(grid, position, UP);
    int downIndex = Maze_GetPosition(grid, position, DOWN);
    int leftIndex = Maze_GetPosition(grid, position, LEFT);
    int rightIndex = Maze_GetPosition(grid, position, RIGHT);

    if (cell.top == OPEN && upIndex != -1 &&
        distanceGrid->distances[upIndex] == -1) {
        _newFrontierIndex++;
        _newFrontier[_newFrontierIndex] = upIndex;
    }

    if (cell.bottom == OPEN && downIndex != -1 &&
        distanceGrid->distances[downIndex] == -1) {
        _newFrontierIndex++;
        _newFrontier[_newFrontierIndex] = downIndex;
        ;
    }

    if (cell.left == OPEN && leftIndex != -1 &&
        distanceGrid->distances[leftIndex] == -1) {
        _newFrontierIndex++;
        _newFrontier[_newFrontierIndex] = leftIndex;
    }

    if (cell.right == OPEN && rightIndex != -1 &&
        distanceGrid->distances[rightIndex] == -1) {
        _newFrontierIndex++;
        _newFrontier[_newFrontierIndex] = rightIndex;
    }
    
    return false;
}