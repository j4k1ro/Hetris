/*
 * File: Structs.c
 * Author: Hieu Do
 * Description: Define functions used to allocate data structures declared in
 * Structs.h
 */

#include "Structs.h"

/* The values of three dimesional array 'shapes' below are defined here. The
 * values then get memcpy() to fill in 'shapes'.
 */
static int tetroI[MAX_SHAPES][MAX_ROW][MAX_COL] = {
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}
    },
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}
    }
};
static int tetroO[MAX_SHAPES][MAX_ROW][MAX_COL] = {
    {
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};
static int tetroJ[MAX_SHAPES][MAX_ROW][MAX_COL] = {
    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    }
};
static int tetroL[MAX_SHAPES][MAX_ROW][MAX_COL] = {
    {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    }
};
static int tetroS[MAX_SHAPES][MAX_ROW][MAX_COL] = {
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    }
};
static int tetroZ[MAX_SHAPES][MAX_ROW][MAX_COL] = {
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0}
    }
};
static int tetroT[MAX_SHAPES][MAX_ROW][MAX_COL] = {
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    }
};

/* Create and set value for a new tetromino. Each tetromino has these
 * properties:
 * topLeft: coordinates of the topleft-most tetromino's block at its current style.
 * shapes: linear array of 4x4 matrices, each one represents 4 positions of a
 *         tetromino, use for rotation
 *         (shapes follows SRS forms, collected from tetris.wikia.com)
 * stylenum: denote the current style of the tetromino. Each tetromino has 4
 *           styles, described in 'shapes'.
 */
tetroType *createTetro (char tetroShape)
{
    tetroType *newTetro = (tetroType *)malloc (sizeof (tetroType));
    newTetro->topLeft = createGridPos (0, 5);
    newTetro->stylenum = 0;
    
    size_t shapesSize = sizeof (newTetro->shapes);

    switch (tetroShape) {
        case 'I':
            memcpy (newTetro->shapes, tetroI, shapesSize);
            break;
        case 'O':
            memcpy (newTetro->shapes, tetroO, shapesSize);
            break;
        case 'J':
            memcpy (newTetro->shapes, tetroJ, shapesSize);
            break;
        case 'L':
            memcpy (newTetro->shapes, tetroL, shapesSize);
            break;
        case 'S':
            memcpy (newTetro->shapes, tetroS, shapesSize);
            break;
        case 'Z':
            memcpy (newTetro->shapes, tetroZ, shapesSize);
            break;
        case 'T':
            memcpy (newTetro->shapes, tetroT, shapesSize);
            break;
    }

    return newTetro;
}

/* Create and set values for the data structure of the game grid. '1' means
 * filled cell and '0' means empty cell.
 * This implementation build the walls by assigning the values of the outter
 * rows and collumns to '1'.
 */
gridType *createGrid (void) 
{
    gridType *newGrid = (gridType *)malloc (sizeof (gridType));
    for (int i = 0; i < MAX_GRID_HEIGHT; i++) {
        for (int j = 0; j < MAX_GRID_WIDTH; j++) {
            if (j == 0 || j == MAX_GRID_WIDTH - 1 || i == MAX_GRID_HEIGHT - 1) {
                newGrid->grid[i][j] = 1;
            }
            else {
                newGrid->grid[i][j] = 0;
            }
        }
    }

    newGrid->isFull = FALSE;
    newGrid->justUpdated = TRUE;
    
    return newGrid;
}

/* Create a 2D vector represents a point in the game grid */
gridPosType *createGridPos (int yPos, int xPos)
{
    gridPosType *newPoint = (gridPosType *)malloc (sizeof (gridPosType));
    newPoint->row = yPos;
    newPoint->col = xPos;

    return newPoint;
}

/* Create a window with 'nLines' lines, 'nCols' columns, and a point starting
 * at (startRow, startCol)
 */
hetArea *createArea (int nLines, int nCols, int startRow, int startCol)
{
    hetArea *newArea = (hetArea *)malloc (sizeof (hetArea));

    newArea->window = newwin (nLines, nCols, startRow, startCol);
    newArea->maxHeight = nLines;
    newArea->maxWidth = nCols;
    newArea->value = 0;

    return newArea;
}
