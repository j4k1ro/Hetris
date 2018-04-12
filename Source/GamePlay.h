/*
 * File: GamePlay.h
 * Author: Hieu Do
 * Description: Declare macros, include sufficient libraries' headers, and
 * function prototypes of GamePlay.c
 */

#ifndef GAMEPLAY_H

# include <time.h>
# include <string.h>
# include <stdlib.h>
# include "Tetris.h"
# include "Structs.h"
# include "Drawing.h"

# define DATETIME_FORMAT "%d/%m/%y - %T"
# define DATETIME_SIZE     20
# define SCORE_SIZE        100
# define SUCCESS           10

# define MAX_RECORDS       20
# define MIN_SCREEN_WIDTH  85
# define MIN_SCREEN_HEIGHT 36

# define GAMEOVER          13

char *determineCurrentTime (void);
void sortScoreRecords (FILE *, char *, int);
void displayScoreRecords (FILE *, int);
void displayGameOverInfo (int);

void displayKeyhint (hetArea *);
void displayScore (hetArea *);
char randomPick (void);

void runGame (void);

# define GAMEPLAY_H
#endif
