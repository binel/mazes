#include "dijkstra.h"

#include <stdlib.h>

DistanceGrid *Maze_InitDistanceGrid(int width, int height) {
    DistanceGrid *grid = (DistanceGrid *)malloc(sizeof(DistanceGrid));
    grid->width = width;
    grid->height = height;
    grid->maxDistance = -1;

    grid->distances = (int *)malloc(width * height * sizeof(int));
    for (int i = 0; i < width * height; i++) {
        grid->distances[i] = -1;
    }
    return grid;
}

void Maze_FreeDistanceGrid(DistanceGrid *grid) { free(grid->distances); }

DistanceGrid *Maze_CalculateDistances(MazeGrid *grid, int startingPosition) {
    DistanceGrid *distanceGrid =
        Maze_InitDistanceGrid(grid->width, grid->height);

	DistanceCalculationState *state = Maze_InitDistanceCalculationState(grid, startingPosition);
	
	while (!state->complete) {
		Maze_CalculateDistances_Process(grid, distanceGrid, state);
	}

    return distanceGrid;
}

DistanceCalculationState *Maze_InitDistanceCalculationState(MazeGrid *grid, int startingPosition) {
	DistanceCalculationState *state = (DistanceCalculationState *)malloc(sizeof(DistanceCalculationState));

    // horrible - do a dynamic array later
    state->frontier = malloc(grid->width * grid->height * sizeof(int));
    state->newFrontier = malloc(grid->width * grid->height * sizeof(int));
    for (int i = 0; i < grid->width * grid->height; i++) {
        state->frontier[i] = -1;
        state->newFrontier[i] = -1;
    }

    state->distance = 0;
    state->frontierIndex = 0;
    state->newFrontierIndex = -1;
    state->frontier[0] = startingPosition;	
    
    return state;
}

void Maze_CalculateDistances_Process(MazeGrid *grid, DistanceGrid *distanceGrid, DistanceCalculationState *state) {
	// TODO some of the ugliest code I've ever written in here, must be a better way 
	
	if (state->complete) {
		return;
	}

	if (state->frontierIndex == -1) {
		// if there is nothing in the new frontier, we are done 
		if (state->newFrontierIndex == -1) {
			distanceGrid->maxDistance = state->distance;
			state->complete = true;
			return;
		}
		
		// move newFrontier to be frontier 
		for (int i = 0; i < state->newFrontierIndex; i++) {
			state->frontier[i] = state->newFrontier[i];
		}
		state->frontierIndex = state->newFrontierIndex;
		state->newFrontierIndex = -1;
		state->distance++;
	}

	distanceGrid->distances[state->frontier[state->frontierIndex]] = state->distance;

	// add connected cells to the new Frontier
	MazeCell cell = grid->cells[state->frontier[state->frontierIndex]];
	int upIndex = Maze_GetPosition(grid, state->frontier[state->frontierIndex], UP);
	int downIndex =
		Maze_GetPosition(grid, state->frontier[state->frontierIndex], DOWN);
	int leftIndex =
		Maze_GetPosition(grid, state->frontier[state->frontierIndex], LEFT);
	int rightIndex =
		Maze_GetPosition(grid, state->frontier[state->frontierIndex], RIGHT);

	if (cell.top == OPEN && upIndex != -1 &&
		distanceGrid->distances[upIndex] == -1) {
		state->newFrontierIndex++;
		state->newFrontier[state->newFrontierIndex] = upIndex;
	}

	if (cell.bottom == OPEN && downIndex != -1 &&
		distanceGrid->distances[downIndex] == -1) {
		state->newFrontierIndex++;
		state->newFrontier[state->newFrontierIndex] = downIndex;
		;
	}

	if (cell.left == OPEN && leftIndex != -1 &&
		distanceGrid->distances[leftIndex] == -1) {
		state->newFrontierIndex++;
		state->newFrontier[state->newFrontierIndex] = leftIndex;
	}

	if (cell.right == OPEN && rightIndex != -1 &&
		distanceGrid->distances[rightIndex] == -1) {
		state->newFrontierIndex++;
		state->newFrontier[state->newFrontierIndex] = rightIndex;
	}

	state->frontierIndex--;	
}