/*
 * draw.h
 *
 * This should contain all logic relating to drawing to the screen using raylib
 *
 */

#ifndef maze_draw_h
#define maze_draw_h

#include <raylib.h>

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
 * @param drawOptions - configuration for how to draw the grid 
 */
void Maze_DrawGrid(MazeGrid *grid, DrawOptions *options);

#endif