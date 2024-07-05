#include "draw.h"

void Maze_DrawGrid(MazeGrid *grid, DrawOptions *options) {
    // figure out how big the cells of the grid should be based on the
    // dimensions of the grid.
    int cell_determinant =
        grid->width < grid->height ? grid->height : grid->width;
    int cell_size = (int)((double)options->width / (double)cell_determinant);
    int half_cell_size = (int)((double)cell_size / 2.0);
    int x = options->xstart;
    int y = options->ystart;
    int position = 0;
    Vector2 start;
    Vector2 end;
    for (int row = 0; row < grid->height; row++) {
        for (int column = 0; column < grid->width; column++) {
            if (grid->cells[position].top == CLOSED) {
            	start.x = x;
            	start.y = y;
            	end.x = x + cell_size;
            	end.y = y;
            	DrawLineEx(start, end, options->wallWidth, WHITE);
            }
            if (grid->cells[position].bottom == CLOSED) {
            	start.x = x;
            	start.y = y + cell_size;
            	end.x = x + cell_size;
            	end.y = y + cell_size;
            	DrawLineEx(start, end, options->wallWidth, WHITE);
            }
            if (grid->cells[position].right == CLOSED) {
            	start.x = x + cell_size;
            	start.y = y;
            	end.x = x + cell_size;
            	end.y = y + cell_size;
                DrawLineEx(start, end, options->wallWidth, WHITE);
            }
            if (grid->cells[position].left == CLOSED) {
            	start.x = x;
            	start.y = y;
            	end.x = x;
            	end.y = y + cell_size;
                DrawLineEx(start, end, options->wallWidth, WHITE);
            }

            if (grid->playerEnabled && grid->playerPosition == position) {
                DrawCircle(x + half_cell_size, y + half_cell_size,
                           half_cell_size, RED);
            }
            x += cell_size;
            position++;
        }
        x = options->xstart;
        y += cell_size;
    }
}

void Maze_ColorMaze(MazeGrid *grid, DistanceGrid *distanceGrid, DrawOptions *options) {
    // figure out how big the cells of the grid should be based on the
    // dimensions of the grid.
    int cell_determinant =
        grid->width < grid->height ? grid->height : grid->width;
    int cell_size = (int)((double)options->width / (double)cell_determinant);
    int x = options->xstart;
    int y = options->ystart;
    int position = 0;
    Vector2 start;
    Vector2 end;
    for (int row = 0; row < grid->height; row++) {
        for (int column = 0; column < grid->width; column++) {
            //DrawRectangle(x, y, x + cell_size, y + cell_size, Fade(GREEN, ((double)distanceGrid->distances[position])/ 10.0));
            DrawRectangle(x, y, x + cell_size, y + cell_size, GREEN);
            x += cell_size;
            position++;
        }
        x = options->xstart;
        y += cell_size;
    }
}