/*
 * File: Tetris.c
 * Author: Hieu Do
 * Description: Define functions control the logic of the game.
 */

#include "Tetris.h"

/* Loop through all possible units that the tetromino, if performing the
 * action, will take places. If one of those places had already been occupied
 * (by comparing with 'landed'), the tetromino won't perform those actions.
 *
 * Return COLLIDE if the tetromino can't perform the action, CLEAR otherwise.
 */
int checkCollision (gridType *landed, tetroType *tetromino, int action)
{
    int stylenum = tetromino->stylenum;
    if (stylenum == MAX_SHAPES) {
        stylenum = 0;
    }
    int tempRow = tetromino->topLeft->row;
    int tempCol = tetromino->topLeft->col;

    switch (action) {
        case DOWN:
            tempRow = tetromino->topLeft->row + 1;
            break;
        case LEFT:
            tempCol = tetromino->topLeft->col - 1;
            break;
        case RIGHT:
            tempCol = tetromino->topLeft->col + 1;
            break;
        case ROTATE:
            break;
        default:
            break;
    }

    for (int row = 0; row < MAX_ROW; row++) {
        for (int col = 0; col < MAX_COL; col++) {
            if (tetromino->shapes[stylenum][row][col] != 0) {
                if (landed->grid[row + tempRow][col + tempCol] != 0) {
                    return COLLIDE;
                }
            }
        }
    }

    tetromino->stylenum = stylenum;

    return CLEAR;
}

/* Move the tetromino down by one unit. Check for possible collision
 * beforehand. If checkCollision() returns COLLIDE, the tetromino has landed,
 * therefore landTetro() is called.
 */
void moveTetroDown (gridType *landed, tetroType *tetromino)
{
    if (checkCollision (landed, tetromino, DOWN) == CLEAR) {
        tetromino->topLeft->row++;
    }
    else {
        landTetro (landed, tetromino);
    }
}

/* Hard drop (move the tetro to the landing area) the tetromino
 * Use moveTetroDown() to move it to the landing area.
 */
void hardDropTetro (gridType *landed, tetroType *tetromino)
{
    while (landed->justUpdated == FALSE) {
        moveTetroDown (landed, tetromino);
    }
}

/* Move the tetromino to the left by one unit.
 * Check for possible collision beforehand.
 */
void moveTetroLeft (gridType *landed, tetroType *tetromino)
{
    if (checkCollision (landed, tetromino, LEFT) == CLEAR) {
        tetromino->topLeft->col--;
    }
}

/* Move the tetromino to the right by one unit.
 * Check for possible collision beforehand.
 */
void moveTetroRight (gridType *landed, tetroType *tetromino)
{
    if (checkCollision (landed, tetromino, RIGHT) == CLEAR) {
        tetromino->topLeft->col++;
    }
}

/* Rotate the tetromino. The style are determined by 'stylenum'
 * Check for possible collision beforehand.
 */
void rotateTetro (gridType *landed, tetroType *tetromino)
{
    tetromino->stylenum++;
    if (checkCollision (landed, tetromino, ROTATE) == COLLIDE) {
        tetromino->stylenum--;
    }
}

/* Updating the values to 'landed' grid by copying values at the right
 * position.
 * After doing this, set 'landed->justUpdated' to TRUE to signal the generation
 * of new tetrominoes.
 */
void landTetro (gridType *landed, tetroType *tetromino)
{
    int style = tetromino->stylenum;
    for (int row = 0; row < MAX_ROW; row++) {
        for (int col = 0; col < MAX_COL; col++) {
            int tRow = tetromino->topLeft->row;
            int tCol = tetromino->topLeft->col;
            int tVal = tetromino->shapes[style][row][col];
            if (tVal != 0) {
                landed->grid[row + tRow][col + tCol] = tVal;
            }
        }
    }
    landed->justUpdated = TRUE;
}

/* Clear the 'lineno' line by copying values of the previous line to it.
 * Same thing happens to the previous lines.
 * Used by updateGridState().
 */
void clearLine (gridType *landed, int lineno)
{
    for (int row = lineno; row > 0; row--) {
        for (int col = 1; col <= MAX_GAME_WIDTH; col++) {
            landed->grid[row][col] = landed->grid[row - 1][col];
        }
    }
}

/* Check the whole grid and see whether there are lines to clear, game is over
 * (the launching area is crowded).
 * Update score when lines are cleared, using this rule:
 * 1 line  (at the same time) =  100 points
 * 2 lines (at the same time) =  200 points
 * 3 lines (at the same time) =  600 points
 * 4 lines (at the same time) = 2400 points
 * (This rule is based on factorial)
 */
void updateGridState (gridType *landed, int *score)
{
    int lineStates[MAX_GAME_HEIGHT] = { 0 };
    int isFull = TRUE;
    int clearCounter = 0;
    
    /* The game can't be continued once the launching area is crowded,
     * therefore 'landed->isFull' is set to TRUE to signal the end of the
     * current game.
     */
    //if (landed->grid[0][5] == 1
    //    || landed->grid[0][6] == 1
    //    || landed->grid[0][7] == 1
    //    || landed->grid[0][8] == 1) {
    //    landed->isFull = TRUE;
    //    return;
    //}
    for (int row = 0; row < MAX_GAME_HEIGHT; row++) {
        isFull = TRUE;
        for (int col = 1; col <= MAX_GAME_WIDTH; col++) {
            if (landed->grid[row][col] == 0) {
                isFull = FALSE;
                break;
            }
        }
        if (isFull) {
            lineStates[row] = TRUE;
        }
    }
    
    for (int line = 0; line < MAX_GAME_HEIGHT; line++) {
        if (lineStates[line] != 0) {
            clearLine (landed, line);
            ++clearCounter;
        }
    }

    switch (clearCounter) {
        case 1:
            *score += 100;
            break;
        case 2:
            *score += 200;
            break;
        case 3:
            *score += 600;
            break;
        case 4:
            *score += 2400;
        default:
            break;
    }
}
