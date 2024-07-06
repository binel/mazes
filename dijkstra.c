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

    // horrible - do a dynamic array later
    int *frontier = malloc(grid->width * grid->height * sizeof(int));
    int *newFrontier = malloc(grid->width * grid->height * sizeof(int));
    for (int i = 0; i < grid->width * grid->height; i++) {
        frontier[i] = -1;
        newFrontier[i] = -1;
    }

    int distance = 0;
    int frontierIndex = 0;
    int newFrontierIndex = -1;
    frontier[0] = startingPosition;
    while (true) {

        while (frontierIndex >= 0) {
            distanceGrid->distances[frontier[frontierIndex]] = distance;

            // add connected cells to the new Frontier
            MazeCell cell = grid->cells[frontier[frontierIndex]];
            int upIndex = Maze_GetPosition(grid, frontier[frontierIndex], UP);
            int downIndex =
                Maze_GetPosition(grid, frontier[frontierIndex], DOWN);
            int leftIndex =
                Maze_GetPosition(grid, frontier[frontierIndex], LEFT);
            int rightIndex =
                Maze_GetPosition(grid, frontier[frontierIndex], RIGHT);

            if (cell.top == OPEN && upIndex != -1 &&
                distanceGrid->distances[upIndex] == -1) {
                newFrontierIndex++;
                newFrontier[newFrontierIndex] = upIndex;
            }

            if (cell.bottom == OPEN && downIndex != -1 &&
                distanceGrid->distances[downIndex] == -1) {
                newFrontierIndex++;
                newFrontier[newFrontierIndex] = downIndex;
                ;
            }

            if (cell.left == OPEN && leftIndex != -1 &&
                distanceGrid->distances[leftIndex] == -1) {
                newFrontierIndex++;
                newFrontier[newFrontierIndex] = leftIndex;
            }

            if (cell.right == OPEN && rightIndex != -1 &&
                distanceGrid->distances[rightIndex] == -1) {
                newFrontierIndex++;
                newFrontier[newFrontierIndex] = rightIndex;
            }

            frontierIndex--;
        }
        // if there is nothing in the new frontier, we are done
        if (newFrontierIndex == -1) {
            distanceGrid->maxDistance = distance;
            break;
        }

        // move newFrontier to be frontier
        for (int i = 0; i <= newFrontierIndex; i++) {
            frontier[i] = newFrontier[i];
        }
        frontierIndex = newFrontierIndex;
        newFrontierIndex = -1;
        distance++;
    }

    return distanceGrid;
}