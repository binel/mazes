#include "grid.h"
#include "memory.h"

void Maze_InitCell(MazeCell *cell) {
    cell->top = CLOSED;
    cell->right = CLOSED;
    cell->bottom = CLOSED;
    cell->left = CLOSED;
}

MazeGrid *Maze_InitGrid(int width, int height) {
    MazeGrid *grid = Maze_malloc(sizeof(MazeGrid));
    grid->cells = Maze_malloc(width * height * sizeof(MazeCell));
    grid->width = width;
    grid->height = height;
    grid->playerPosition = 0;
    grid->playerEnabled = true;
    int i = 0;
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            MazeCell cell;
            Maze_InitCell(&cell);
            grid->cells[i] = cell;
            i++;
        }
    }

    return grid;
}

MazeGrid *Maze_ResizeGrid(MazeGrid *grid, int width, int height) {
    Maze_FreeGrid(grid);
    MazeGrid *newGrid = Maze_InitGrid(width, height);
    return newGrid;
}

MazeGrid *Maze_IncreaseGridWidth(MazeGrid *grid) {
    return Maze_ResizeGrid(grid, grid->width + 1, grid->height);
}

MazeGrid *Maze_DecreaseGridWidth(MazeGrid *grid) {
    return Maze_ResizeGrid(grid, grid->width - 1, grid->height);
}

MazeGrid *Maze_IncreaseGridHeight(MazeGrid *grid) {
    return Maze_ResizeGrid(grid, grid->width, grid->height + 1);
}

MazeGrid *Maze_DecreaseGridHeight(MazeGrid *grid) {
    return Maze_ResizeGrid(grid, grid->width, grid->height - 1);
}

void Maze_ResetGrid(MazeGrid *grid) {
    grid->playerPosition = 0;
    grid->playerEnabled = true;
    int i = 0;
    for (int row = 0; row < grid->height; row++) {
        for (int column = 0; column < grid->width; column++) {
            Maze_InitCell(&grid->cells[i]);
            i++;
        }
    }
}

int Maze_GetPosition(MazeGrid *grid, int position, enum Direction direction) {

    // error handling
    // top row
    if (position < grid->width && direction == UP) {
        return -1;
    }

    // bottom row
    if (position > grid->width * (grid->height - 1) - 1 && direction == DOWN) {
        return -1;
    }

    // right column
    if (position != 0 && (position + 1) % grid->width == 0 &&
        direction == RIGHT) {
        return -1;
    }
    // left column
    if (position % grid->width == 0 && direction == LEFT) {
        return -1;
    }

    if (direction == UP) {
        return position - grid->width;
    }

    if (direction == RIGHT) {
        return position + 1;
    }

    if (direction == DOWN) {
        return position + grid->width;
    }

    if (direction == LEFT) {
        return position - 1;
    }

    return -1;
}

int Maze_RemoveWall(MazeGrid *grid, int position, enum Direction direction) {
    if (position < 0 || position > grid->width * grid->height) {
        return 0;
    }

    int neighborPosition = Maze_GetPosition(grid, position, direction);
    if (neighborPosition == -1) {
        // Just update the single cell - useful for opening exits and entrances
        switch (direction) {
        case UP:
            grid->cells[position].top = OPEN;
            break;
        case DOWN:
            grid->cells[position].bottom = OPEN;
            break;
        case LEFT:
            grid->cells[position].left = OPEN;
            break;
        case RIGHT:
            grid->cells[position].right = OPEN;
            break;
        }
    }

    switch (direction) {
    case UP:
        grid->cells[position].top = OPEN;
        grid->cells[neighborPosition].bottom = OPEN;
        break;
    case DOWN:
        grid->cells[position].bottom = OPEN;
        grid->cells[neighborPosition].top = OPEN;
        break;
    case LEFT:
        grid->cells[position].left = OPEN;
        grid->cells[neighborPosition].right = OPEN;
        break;
    case RIGHT:
        grid->cells[position].right = OPEN;
        grid->cells[neighborPosition].left = OPEN;
        break;
    }

    return 1;
}

int Maze_HasNeighbor(MazeGrid *grid, int position, enum Direction direction) {
    if (Maze_GetPosition(grid, position, direction) != -1) {
        return 1;
    } else {
        return 0;
    }
}

static int IsBlocked(MazeGrid *grid, int position, enum Direction direction) {
    switch (direction) {
    case UP:
        return grid->cells[position].top == CLOSED;
    case DOWN:
        return grid->cells[position].bottom == CLOSED;
    case LEFT:
        return grid->cells[position].left == CLOSED;
    case RIGHT:
        return grid->cells[position].right == CLOSED;
    }
    return 0;
}

int Maze_MovePlayerInDirection(MazeGrid *grid, enum Direction direction) {
    int moveToPosition =
        Maze_GetPosition(grid, grid->playerPosition, direction);

    if (moveToPosition == -1) {
        return 0;
    }

    if (IsBlocked(grid, grid->playerPosition, direction)) {
        return 0;
    }

    grid->playerPosition = moveToPosition;
    return 1;
}

void Maze_SetStartOfMaze_Random(MazeGrid *grid) {
	grid->startingPosition = rand() % (grid->width * grid->height);
}

void Maze_SetEndOfMaze_Random(MazeGrid *grid) {
	grid->endingPosition = rand() % (grid->width * grid->height);
}

void Maze_FreeGrid(MazeGrid *grid) {
    Maze_free(grid->cells);
    Maze_free(grid);
}

void Maze_SetIfWon(MazeGrid *grid) {
    grid->won = grid->playerPosition == grid->endingPosition;
}
