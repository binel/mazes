#include "generator.h"
#include "memory.h"



void Maze_RandomWalk(MazeGrid *grid) {
    RandomWalkState state;
    Maze_RandomWalk_InitState(grid, &state);

    while (state.unvisited > 0) {
        Maze_RandomWalk_Process(grid, &state);
    }
}

void Maze_RandomWalk_Process(MazeGrid *grid, RandomWalkState *state) {
    if (state->unvisited == 0) {
        state->finished = true;
        return;
    }

    // unfortunately we have to check if the cell we are already in
    // was visited to handle the startup condition. There might be
    // a better way to do this
    if (!state->visited[state->position]) {
        state->visited[state->position] = true;
    }

    int direction = rand() % 4;
    int newPosition;
    switch (direction) {
    case 0:
        newPosition = Maze_GetPosition(grid, state->position, UP);
        break;
    case 1:
        newPosition = Maze_GetPosition(grid, state->position, DOWN);
        break;
    case 2:
        newPosition = Maze_GetPosition(grid, state->position, LEFT);
        break;
    case 3:
        newPosition = Maze_GetPosition(grid, state->position, RIGHT);
        break;
    }

    if (newPosition == -1) {
        return;
    }

    if (!state->visited[newPosition]) {
        switch (direction) {
        case 0:
            Maze_RemoveWall(grid, state->position, UP);
            break;
        case 1:
            Maze_RemoveWall(grid, state->position, DOWN);
            break;
        case 2:
            Maze_RemoveWall(grid, state->position, LEFT);
            break;
        case 3:
            Maze_RemoveWall(grid, state->position, RIGHT);
            break;
        }
        state->unvisited -= 1;
        state->visited[newPosition] = true;
    }

    state->position = newPosition;
}

void Maze_RandomWalk_InitState(MazeGrid *grid, RandomWalkState *state) {
    state->position = rand() % (grid->width * grid->height);
    state->unvisited = (grid->width * grid->height) - 1;
    state->visited =
        (bool *)Maze_malloc(grid->width * grid->height * sizeof(bool));
    state->finished = false;
}