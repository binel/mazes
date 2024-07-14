#include "binaryTree.h"

static int _position;
static int _maxPosition;

void Maze_BinaryTree(MazeGrid *grid) {
    Maze_BinaryTree_Reset(grid);
    bool done = false;
    while (!done) {
        done = Maze_BinaryTree_Process(grid);
    }
}

bool Maze_BinaryTree_Process(MazeGrid *grid) {
    if (_position > _maxPosition) {
        return true;
    }

    // if there is a down and right neighbor, randomly pick one to open
    int hasDown = Maze_HasNeighbor(grid, _position, DOWN);
    int hasRight = Maze_HasNeighbor(grid, _position, RIGHT);
    if (hasDown && hasRight) {
        if (rand() % 2 == 0) {
            Maze_RemoveWall(grid, _position, DOWN);
        } else {
            Maze_RemoveWall(grid, _position, RIGHT);
        }
    }
    // if only south or east, open that one
    else if (hasDown) {
        Maze_RemoveWall(grid, _position, DOWN);
    } else if (hasRight) {
        Maze_RemoveWall(grid, _position, RIGHT);
    }
    _position++;

    return false;
}

void Maze_BinaryTree_Reset(MazeGrid *grid) {
    _position = 0;
    _maxPosition = (grid->width * grid->height) - 1;
}
