#include "dijkstra.h"
#include "memory.h"

#include <stdlib.h>

DistanceGrid *Maze_InitDistanceGrid(int width, int height) {
    DistanceGrid *grid = (DistanceGrid *)Maze_malloc(sizeof(DistanceGrid));
    grid->width = width;
    grid->height = height;
    grid->maxDistance = -1;

    grid->distances = (int *)Maze_malloc(width * height * sizeof(int));
    for (int i = 0; i < width * height; i++) {
        grid->distances[i] = -1;
    }
    return grid;
}

void Maze_FreeDistanceGrid(DistanceGrid *grid) { free(grid->distances); }

DistanceGrid *Maze_CalculateDistances(MazeGrid *grid, int startingPosition) {
    DistanceGrid *distanceGrid =
        Maze_InitDistanceGrid(grid->width, grid->height);

    DistanceCalculationState *state =
        Maze_InitDistanceCalculationState(grid, startingPosition);

    while (!state->complete) {
        Maze_CalculateDistances_Process(grid, distanceGrid, state);
    }

    return distanceGrid;
}

DistanceCalculationState *
Maze_InitDistanceCalculationState(MazeGrid *grid, int startingPosition) {
    DistanceCalculationState *state = (DistanceCalculationState *)Maze_malloc(
        sizeof(DistanceCalculationState));

    // horrible - do a dynamic array later
    state->frontier = Maze_malloc(grid->width * grid->height * sizeof(int));
    state->newFrontier = Maze_malloc(grid->width * grid->height * sizeof(int));
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

void Maze_CalculateDistances_Process(MazeGrid *grid, DistanceGrid *distanceGrid,
                                     DistanceCalculationState *state) {
    // TODO some of the ugliest code I've ever written in here, must be a better
    // way

    if (state->complete) {
        return;
    }

    if (state->frontierIndex == -1) {
        // if there is nothing in the new frontier, we are done
        if (state->newFrontierIndex == -1) {
            state->complete = true;
            return;
        }

        // move newFrontier to be frontier
        for (int i = 0; i <= state->newFrontierIndex; i++) {
            state->frontier[i] = state->newFrontier[i];
        }
        state->frontierIndex = state->newFrontierIndex;
        state->newFrontierIndex = -1;
        state->distance++;
        distanceGrid->maxDistance = state->distance;
    }

    int position = state->frontier[state->frontierIndex];
    distanceGrid->distances[position] = state->distance;
    state->frontierIndex -= 1;
    // add connected cells to the new Frontier

    MazeCell cell = grid->cells[position];
    int upIndex = Maze_GetPosition(grid, position, UP);
    int downIndex = Maze_GetPosition(grid, position, DOWN);
    int leftIndex = Maze_GetPosition(grid, position, LEFT);
    int rightIndex = Maze_GetPosition(grid, position, RIGHT);

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
}