/*
 * File: Drawing.c
 * Author: Hieu Do
 * Description: Perform the main task of drawing characters during the game.
 */

#include "Drawing.h"

/* Draw unit block on the window pointed to by 'gameWin' */
void drawUnit (WINDOW *gameWin, int y, int x)
{
    mvwprintw (gameWin, y,     x, "+---+");
    mvwprintw (gameWin, y + 1, x, "| O |");
    mvwprintw (gameWin, y + 2, x, "+---+");
}

/* Render landed grid on the screen */
void renderGrid (WINDOW *gameWin, gridType *landed)
{
    int x = 0;
    int y = 0;

    for (int row = 0; row <= MAX_GAME_HEIGHT; row++) {
        for (int col = 1; col <= MAX_GAME_WIDTH; col++) {
            if (landed->grid[row][col]) {
                drawUnit (gameWin, y, x);
            }
            x += UNIT_WIDTH;
        }
        x = 0;
        y += UNIT_HEIGHT;
    }
    wnoutrefresh (gameWin);
}

/* Draw tetromino shape reprensented by 'shape' on the window pointed to by
 * 'gameWin', starting from the point (startY, startX)
 */
void drawShape (WINDOW *gameWin, int shape[MAX_ROW][MAX_COL], int startY, int startX)
{
    int y = startY * UNIT_HEIGHT, x = startX * UNIT_WIDTH;

    for (int row = 0; row < MAX_ROW; row++) {
        for (int col = 0; col < MAX_COL; col++) {
            if (shape[row][col] != 0) {
                drawUnit (gameWin, y, x);
            }
            x += UNIT_WIDTH;
        }
        x = startX * UNIT_WIDTH; 
        y += UNIT_HEIGHT;
    }
}

/* Set values accordingly, then call drawShape() to draw the tetromino */
void renderTetromino (WINDOW *gameWin, tetroType *tetromino)
{
    int x = tetromino->topLeft->col - 1;
    int y = tetromino->topLeft->row;

    int style = tetromino->stylenum;
    drawShape (gameWin, tetromino->shapes[style], y, x);
    wnoutrefresh (gameWin);
}
