#include "sidewinder.h"
#include "generator.h"

static int _runLength;
static int _position;
static int _maxPosition;

void Maze_Sidewinder(MazeGrid *grid) {
    Maze_Sidewinder_Reset(grid);

    while (!Maze_Sidewinder_Process(grid)) {
    }
}

bool Maze_Sidewinder_Process(MazeGrid *grid) {
    if (_position >= _maxPosition) {
        return true;
    }

    int hasDown = Maze_HasNeighbor(grid, _position, DOWN);
    int hasRight = Maze_HasNeighbor(grid, _position, RIGHT);
    _runLength++;
    // should end run
    if (!hasRight || (hasDown && rand() % 2 == 0)) {
        int openDownPos = _position - (rand() % _runLength);
        Maze_RemoveWall(grid, openDownPos, DOWN);

        _runLength = 0;
    } else {
        Maze_RemoveWall(grid, _position, RIGHT);
    }
    _position++;

    return false;
}

void Maze_Sidewinder_Reset(MazeGrid *grid) {
    _position = 0;
    _runLength = 0;
    _maxPosition = (grid->width * grid->height) - 1;
}
