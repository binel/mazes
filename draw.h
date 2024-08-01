/*
 * draw.h
 *
 * This should contain all logic relating to drawing to the screen using raylib
 *
 */

#ifndef maze_draw_h
#define maze_draw_h

#include <raylib.h>

#include "dijkstra.h"
#include "grid.h"
#include "ui.h" 

/*
 * Configuration options for drawing the grid
 *
 */
typedef struct {
    // x offset padding in px
    int xstart;
    // y offset padding in px
    int ystart;
    // the width of the grid in px
    int width;
    // the height of the grid in px
    int height;
} DrawOptions;

/*
 * Draws a maze onto the screen
 */
void Maze_DrawGrid(MazeGrid *grid, DrawOptions *options);

/*
 * Colors the maze based on the distance from the starting cell. Cells closer to
 * the starting cell are light green and get darker as distance from the
 * starting cell increases.
 *
 */
void Maze_ColorMaze(MazeGrid *grid, DistanceGrid *distanceGrid,
                    DrawOptions *options);

void Maze_DrawButton(Button button);

#endif
