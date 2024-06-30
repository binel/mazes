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
 * Draws a maze onto the screen 
 * 
 * @param grid the grid to be displayed 
 * @param xstart the x offset or padding in px to start drawing the 
 * 		  top left corner of the grid
 * @param ystart the y offset or padding in px to start drawing the
 *		  top right corner of the grid
 * @param width the width of the grid in px 
 * @param height the height of the grid in px 
 */
void Maze_DrawGrid(MazeGrid* grid, int xstart, int ystart, int width, int height);

#endif