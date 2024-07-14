#include "randomWalk.h"
#include "memory.h"

static int _position;
static int _unvisited;
static int _maxPosition; 

static bool *_visited = NULL; 

void Maze_RandomWalk(MazeGrid *grid) {
    Maze_RandomWalk_Reset(grid);

    while (_unvisited > 0) {
        Maze_RandomWalk_Process(grid);
    }
}

bool Maze_RandomWalk_Process(MazeGrid *grid) {
    if (_unvisited == 0) {
        return true;
    }

    // unfortunately we have to check if the cell we are already in
    // was visited to handle the startup condition. There might be
    // a better way to do this
    if (!_visited[_position]) {
        _visited[_position] = true;
    }

    int direction = rand() % 4;
    int newPosition;
    switch (direction) {
    case 0:
        newPosition = Maze_GetPosition(grid, _position, UP);
        break;
    case 1:
        newPosition = Maze_GetPosition(grid, _position, DOWN);
        break;
    case 2:
        newPosition = Maze_GetPosition(grid, _position, LEFT);
        break;
    case 3:
        newPosition = Maze_GetPosition(grid, _position, RIGHT);
        break;
    }

    if (newPosition == -1) {
        return false;
    }

    if (!_visited[newPosition]) {
        switch (direction) {
        case 0:
            Maze_RemoveWall(grid, _position, UP);
            break;
        case 1:
            Maze_RemoveWall(grid, _position, DOWN);
            break;
        case 2:
            Maze_RemoveWall(grid, _position, LEFT);
            break;
        case 3:
            Maze_RemoveWall(grid, _position, RIGHT);
            break;
        }
        _unvisited -= 1;
        _visited[newPosition] = true;
    }

    _position = newPosition;
    
    return false;
}

void Maze_RandomWalk_Reset(MazeGrid *grid) {
	if (_visited != NULL) {
		Maze_free(_visited);
	}

    _position = rand() % (grid->width * grid->height);
    _unvisited = (grid->width * grid->height) - 1;
    _visited =
        (bool *)Maze_malloc(grid->width * grid->height * sizeof(bool));
}