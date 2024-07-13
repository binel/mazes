#ifndef maze_grid_h
#define maze_grid_h

#include <stdbool.h>
#include <stdlib.h>

/*
 * Describes if the wall of a cell exists or not
 */
enum WallType {
    OPEN,
    CLOSED,
};

/*
 * Cardinal directions
 */
enum Direction { UP, RIGHT, DOWN, LEFT };

/*
 * Struct for a single cell of the maze
 */
typedef struct {
    // State of the top (north) wall
    enum WallType top;
    // State of the bottom (south) wall
    enum WallType bottom;
    // State of the left (west) wall
    enum WallType left;
    // State of the right (east) wall
    enum WallType right;
} MazeCell;

/*
 * Struct for holding the state of the maze
 */
typedef struct {
    // The width of the maze in cells
    int width;
    // The height of the maze in cells
    int height;
    // The cell array - there are width*height cells
    MazeCell *cells;
    // TODO split out the player stuff
    // The position is the maze that the player currently is
    int playerPosition;
    // True if the player should be drawn
    bool playerEnabled;
} MazeGrid;

/*
 * Initializes a single cell
 *
 * @param cell - the cell to initialize
 */
void Maze_InitCell(MazeCell *cell);

/*
 * Initializes a grid with the given width and height. All cells start out
 * fully closed
 *
 * @param width - the width of the grid in cells
 * @param height - the height of the grid in cells
 */
MazeGrid *Maze_InitGrid(int width, int height);

/*
 * Resizes the grid to have the given width and height. This does not 
 * preserve the state of the cells within the grid 
 *
 * @param grid - the old grid to resize 
 * @param width - the new width of the grid 
 * @param height - the new height of the grid
 */
MazeGrid *Maze_ResizeGrid(MazeGrid *grid, int width, int height); 

MazeGrid *Maze_IncreaseGridWidth(MazeGrid *grid);

MazeGrid *Maze_DecreaseGridWidth(MazeGrid *grid);

MazeGrid *Maze_IncreaseGridHeight(MazeGrid *grid);

MazeGrid *Maze_DecreaseGridHeight(MazeGrid *grid);

void Maze_ResetGrid(MazeGrid *grid);

/*
 * Releases the memory of the given grid
 *
 * @param grid - the grid to free
 */
void Maze_FreeGrid(MazeGrid *grid);

/*
 * Returns the position of the cell that is in the provided direction from the
 * given cell. This is used to answer the question "what is the position of
 * the cell above this one?
 *
 * @param grid - the grid we are working with
 * @param position - the position of the reference cell
 * @param direction - the direction relative to the "position" cell that we want
 * to find the position of
 *
 */
int Maze_GetPosition(MazeGrid *grid, int position, enum Direction direction);

/*
 * Returns 1 if the cell has a neighbor in the provided direction, 0 if it does
 * not
 * TODO have this return a bool
 *
 * @param grid - the grid we are working with
 * @param position - the position of the reference cell
 * @param the direction relative to the reference cell that we want to see if a
 * cell exists at
 *
 */
int Maze_HasNeighbor(MazeGrid *grid, int position, enum Direction direction);

/*
 * Move the player position in the provided direction, if possible. If the move
 * is not possible, the player does not move.
 * TODO clarify return
 *
 * @param grid - the grid we are working with
 * @param direction - the direction to move the player
 *
 */
int Maze_MovePlayerInDirection(MazeGrid *grid, enum Direction direction);

/*
 * Remove the wall between two cells. You only need to call this once (i.e. you
 * don't need to remove the right wall from position 1 and the left wall from
 * position 2)
 *
 * @param grid - the grid we are working with
 * @param position - the position of the reference cell
 * @param direction - the wall to remove
 *
 */
int Maze_RemoveWall(MazeGrid *grid, int position, enum Direction direction);

#endif