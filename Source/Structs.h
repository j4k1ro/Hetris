/*
 * File: Structs.h
 * Author: Hieu Do
 * Description: Declare data structures used for storing the game states,
 *  including the grid and tetrominoes; plus function prototypes for creating
 *  objects of declared structs.
 */

#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

#ifndef STRUCTS_H


# define MAX_COL 4
# define MAX_ROW 4
# define MAX_SHAPES 4

# define MAX_GRID_WIDTH  14
# define MAX_GRID_HEIGHT 18

typedef struct {
    int grid[MAX_GRID_HEIGHT][MAX_GRID_WIDTH];
    int isFull;
    int justUpdated;
} gridType;

typedef struct {
    int shapes[MAX_SHAPES][MAX_ROW][MAX_COL];
    struct gridPos *topLeft;
    int stylenum;
} tetroType;

typedef struct gridPos {
    int row;
    int col;
} gridPosType;

typedef struct {
    WINDOW *window;
    int maxHeight;
    int maxWidth;
    int value; //for score only
} hetArea;

tetroType *createTetro (char);
gridType *createGrid (void);
gridPosType *createGridPos (int, int);
hetArea *createArea (int, int, int, int);

# define STRUCTS_H
#endif
