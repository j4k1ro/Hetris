/*
 * File: Drawing.h
 * Author: Hieu Do
 * Description: Declare macros, include sufficient libraries' headers and
 * function prototypes for Drawing.c
 */

#ifndef DRAWING_H

# include <ncurses.h>
# include "Structs.h"

# define UNIT_WIDTH 4
# define UNIT_HEIGHT 2
# define MAX_GAME_WIDTH  12
# define MAX_GAME_HEIGHT 17

void renderTetromino (WINDOW *, tetroType *);
void renderGrid (WINDOW *, gridType *);
void drawUnit (WINDOW *, int, int);
void drawShape (WINDOW *, int [][MAX_COL], int, int);

# define DRAWING_H
#endif
