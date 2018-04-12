/*
 * File: Tetris.h
 * Author: Hieu Do
 * Description: Declare macros, include sufficient libraries' headers and
 * function prototypes for Tetris.c
 */

#ifndef TETRIS_H

# include "Structs.h"
# include "Drawing.h"
# include <ncurses.h>

# define COLLIDE 2
# define CLEAR   3

# define ROTATE  4
# define RIGHT   5
# define DOWN    6
# define LEFT    7

int checkCollision (gridType *, tetroType *, int);
void moveTetroDown (gridType *, tetroType *);
void hardDropTetro (gridType *, tetroType *);
void moveTetroLeft (gridType *, tetroType *);
void moveTetroRight (gridType *, tetroType *);
void rotateTetro (gridType *, tetroType *);
void landTetro (gridType *, tetroType *);
void clearLine (gridType *, int);
void updateGridState (gridType *, int *);

# define TETRIS_H
#endif
