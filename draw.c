#include <stdio.h>

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
    int x_midpoint = options->xstart + (options->width / 2);
    int y_midpoint = options->ystart + (options->height / 2);

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
                DrawLineEx(start, end, 1, WHITE);
            }
            if (grid->cells[position].bottom == CLOSED) {
                start.x = x;
                start.y = y + cell_size;
                end.x = x + cell_size;
                end.y = y + cell_size;
                DrawLineEx(start, end, 1, WHITE);
            }
            if (grid->cells[position].right == CLOSED) {
                start.x = x + cell_size;
                start.y = y;
                end.x = x + cell_size;
                end.y = y + cell_size;
                DrawLineEx(start, end, 1, WHITE);
            }
            if (grid->cells[position].left == CLOSED) {
                start.x = x;
                start.y = y;
                end.x = x;
                end.y = y + cell_size;
                DrawLineEx(start, end, 1, WHITE);
            }

            if (grid->playerEnabled && grid->playerPosition == position) {
                DrawCircle(x + half_cell_size, y + half_cell_size,
                           half_cell_size, RED);
            }
            
            if (position == grid->startingPosition) {
            	int width = MeasureText("S", 16);
            	int height = 16; 
            	DrawText("S", x + half_cell_size - (width / 2), y + half_cell_size - (height / 2), 16, RED);
            }
            
            if (position == grid->endingPosition) {
            	int width = MeasureText("E", 16);
            	int height = 16;
            	DrawText("E", x + half_cell_size - (width / 2), y + half_cell_size - (height / 2), 16, GREEN);
            }
            
            x += cell_size;
            position++;
        }
        x = options->xstart;
        y += cell_size;
    }

    if (grid->won) {
        DrawText("You Win!", x_midpoint - (MeasureText("You Win!", 64) / 2) , y_midpoint - 32, 64, WHITE);
    }
}

void Maze_ColorMaze(MazeGrid *grid, DistanceGrid *distanceGrid,
                    DrawOptions *options) {
    // don't do any coloring if nothing has been calculated
    if (!distanceGrid->calculated) {
        return;
    }

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
            float brightness = ((float)distanceGrid->distances[position] /
                                (float)distanceGrid->maxDistance);
            DrawRectangle(x, y, cell_size, cell_size, Fade(GREEN, brightness));

            // this should be a draw options
            char str[4];
            sprintf(str, "%d", distanceGrid->distances[position]);
            // snuggled up in top left corner 
            DrawText(str, x + 2, y + 2, 8, WHITE);

            x += cell_size;
            position++;
        }
        x = options->xstart;
        y += cell_size;
    }
}

void Maze_DrawButton(Button button) {
    // border 
    DrawRectangle(button.xStart, button.yStart, button.width, button.height, WHITE);
    // background 
    DrawRectangle(button.xStart + 5, button.yStart + 5, button.width - 10, button.height - 10, RED);
}
