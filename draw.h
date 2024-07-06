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
    // the width of the walls of the cell
    int wallWidth;
} DrawOptions;

/*
 * Draws a maze onto the screen
 *
 * @param grid - the grid to be displayed
 * @param options - configuration for how to draw the grid
 */
void Maze_DrawGrid(MazeGrid *grid, DrawOptions *options);

/*
 * Colors the maze based on the distance from the starting cell. Cells closer to
 * the starting cell are light green and get darker as distance from the
 * starting cell increases.
 *
 * @param grid - the grid to be displayed
 * @param distanceGrid - the calculated distances to be used to color the grid
 * @param options - configuration on how to draw the grid
 */
void Maze_ColorMaze(MazeGrid *grid, DistanceGrid *distanceGrid,
                    DrawOptions *options);

#endif