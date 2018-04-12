/*
 * File: GamePlay.c
 * Author: Hieu Do
 * Description: Defintion of functions related to operate the game and display
 * texts.
 */

#include <ncurses.h>
#include "GamePlay.h"

char *determineCurrentTime (void)
{
    time_t currentTime;
    struct tm *brokenDownTime;
    char *datetime = (char *)malloc (DATETIME_SIZE);

    (void) time (&currentTime);
    brokenDownTime = localtime (&currentTime);
    (void) strftime (datetime, DATETIME_SIZE, DATETIME_FORMAT, brokenDownTime);

    return datetime;
}

void sortScoreRecords (FILE *highscore, char *datetime, int score)
{
    endwin ();
    (void) system ("if [ ! -f highscore.txt ]; then touch highscore.txt; fi");
    (void) system ("cp highscore.txt temp");

    /* Open file highscore.txt to write new record */
    highscore = fopen ("./highscore.txt", "w");
    fprintf (highscore, "%-19s%15i\n", datetime, score);
    fclose (highscore);
    (void) system ("cat temp >> highscore.txt && rm temp");

    /* Returns to ncurses */
    wrefresh (stdscr);
}

void displayScoreRecords (FILE *highscore, int status)
{
    /* Create a window to display score records (first 10 only) */
    WINDOW *scoreRec = newwin (0, 0, 0, 0);
    int maxWidth, maxHeight;
    getmaxyx (scoreRec, maxHeight, maxWidth);

    wattron (scoreRec, A_BOLD);
    if (status == GAMEOVER) {
        mvwprintw (scoreRec, 2, maxWidth / 2 - 5, "GAME OVER");
    }
    mvwprintw (scoreRec, 4, maxWidth / 2 - 3, "SCORES");
    wattroff (scoreRec, A_BOLD);

    mvwprintw (scoreRec, 6, maxWidth / 2 - 15, "%19s%15s", "DATE/TIME", "SCORE");

    /* Open file highscore.txt to read records and put them to the window */
    
    highscore = fopen ("./highscore.txt", "r");
    if (highscore == NULL) {
        mvwprintw (scoreRec, 8, maxWidth / 2 - 12, "You haven't played yet!");
        mvwprintw (scoreRec, maxHeight - 2, maxWidth / 2 - 13, "Press any key to continue...");
        wgetch (scoreRec);

        werase (scoreRec);
        wrefresh (scoreRec);
        delwin (scoreRec);
        return;
    }
    char *scoreLine = (char *)malloc (SCORE_SIZE + 1);
    int line = 8, recordCounter = 0;

    while (fgets (scoreLine, SCORE_SIZE, highscore) && recordCounter < MAX_RECORDS) {
        mvwprintw (scoreRec, line++, maxWidth / 2 - 15, scoreLine);
        ++recordCounter;
    }
    fclose (highscore);

    mvwprintw (scoreRec, maxHeight - 2, maxWidth / 2 - 13, "Press any key to continue...");
    box (scoreRec, 0, 0);

    (void) wgetch (scoreRec);

    werase (scoreRec);
    wrefresh (scoreRec);
    delwin (scoreRec);

    free (scoreLine);
    scoreLine = NULL;
}

/* At the end of the game, update the high score list and display it.
 * Time are taken for recording.
 */
void displayGameOverInfo (int score)
{
    /* Get the current time */
    char *datetime = determineCurrentTime ();

    /* Create a new record, and store them by time created. When that is done,
     * display them.
     */
    FILE *highscore = NULL;
    sortScoreRecords (highscore, datetime, score);
    displayScoreRecords (highscore, GAMEOVER);

    free (datetime);
    datetime =  NULL;
}

char randomPick (void)
{
    static char tetrominoes[] = {'I', 'J', 'L', 'S', 'T', 'Z', 'O'};
    return tetrominoes[rand () % 7];
}

void updateScoreState (hetArea *scoreArea, int score)
{
    scoreArea->value = score;
    mvwprintw (scoreArea->window, 1, 1, "SCORE");
    mvwprintw (scoreArea->window, 2, 1, "%i", score);
    wrefresh (scoreArea->window);
}

void displayKeyhint (hetArea *keyhintArea)
{
    int line = keyhintArea->maxHeight / 2 - 6;
    int col = keyhintArea->maxWidth / 2 - 8;

    mvwprintw (keyhintArea->window, line - 2, col + 2, "KEYS REMINDER");

    mvwprintw (keyhintArea->window, line++, col, "Rotate:");
    mvwprintw (keyhintArea->window, line++, col, "[UP] [W] [K]");
    mvwprintw (keyhintArea->window, line++, col, "");
    mvwprintw (keyhintArea->window, line++, col, "Move left:");
    mvwprintw (keyhintArea->window, line++, col, "[LEFT]  [A] [H]");
    mvwprintw (keyhintArea->window, line++, col, "");
    mvwprintw (keyhintArea->window, line++, col, "Move right:");
    mvwprintw (keyhintArea->window, line++, col, "[RIGHT] [D] [L]");
    mvwprintw (keyhintArea->window, line++, col, "");
    mvwprintw (keyhintArea->window, line++, col, "Soft drop:");
    mvwprintw (keyhintArea->window, line++, col, "[DOWN]  [S] [J]");
    mvwprintw (keyhintArea->window, line++, col, "");
    mvwprintw (keyhintArea->window, line++, col, "Hard drop:");
    mvwprintw (keyhintArea->window, line,   col, "[SPACE]");
    wnoutrefresh (keyhintArea->window);
}

void displayScore (hetArea *scoreArea)
{
    int line = scoreArea->maxHeight / 2 - 2;
    int col = scoreArea->maxWidth / 2 - 6;

    mvwprintw (scoreArea->window, line - 2, col + 2, "SCORE RULE");

    mvwprintw (scoreArea->window, line++, col, "1 -> 100  pts");
    mvwprintw (scoreArea->window, line++, col, "2 -> 200  pts");
    mvwprintw (scoreArea->window, line++, col, "3 -> 600  pts");
    mvwprintw (scoreArea->window, line,   col, "4 -> 2400 pts");
    wnoutrefresh (scoreArea->window);
}

void runGame (void)
{
    gridType *landed = createGrid ();
    tetroType *currentTetro = NULL;

    initscr ();
    cbreak ();
    noecho ();
    curs_set (0);

    int maxLines = LINES;

    /* Create areas in the main game. Hardcoded */
    hetArea *keyhintArea = createArea (maxLines - 1, 19, 0, 0);
    hetArea *gameArea  = createArea (maxLines - 1, 49, 0, 19);
    hetArea *scoreArea = createArea (maxLines - 1, 17, 0, 68);

    /* Decorate those areas */
    box (scoreArea->window, 0, 0);
    box (keyhintArea->window, 0, 0);
    wborder (gameArea->window, '|', '|', '-', '-', '+', '+', '+', '+');

    displayKeyhint (keyhintArea);
    displayScore (scoreArea);

    wnoutrefresh (scoreArea->window);
    wnoutrefresh (keyhintArea->window);
    doupdate ();
    
    /* Only the 'gameArea' window should be set these settings */
    keypad (gameArea->window, TRUE);
    nodelay (gameArea->window, TRUE);

    int score = 0;
    srand (time (NULL));
    int tick = 0;
    int delay = 30000;
    while (1) {
        tick++;

        /* If landed grid has just been updated, it had also been drawn, but it
         * is also a signal to generate a new tetromino. If landed grid is
         * full, it had already been signal at the end of this while loop.
         *
         * It is initialized to TRUE to generate a new tetromino at the
         * beginning of the game
         */
        if (landed->justUpdated) {
            currentTetro = createTetro (randomPick ());
            if (checkCollision (landed, currentTetro, DOWN) == COLLIDE) {
                landed->isFull = TRUE;
            }

            if (landed->isFull) {
                break;
            }

            /* Always update grid state after the tetromino has landed
             * (therefore landed->justUpdated == TRUE).
             */
            updateGridState (landed, &score);
            /* Update the score state on the score window, based on the score
             * set when updateGridState() returns
             */ 
            updateScoreState (scoreArea, score);

            landed->justUpdated = FALSE;
        }

        /* Render the landed grid. When the first tetromino has not yet landed,
         * it means a blank screen. 
         */
        werase (gameArea->window);
        wborder (gameArea->window, '|', '|', '-', '-', '+', '+', '+', '+');
        renderGrid (gameArea->window, landed);
        /* Always render the current tetromino */
        renderTetromino (gameArea->window, currentTetro);
        doupdate ();

        /* This is the time to make the tetromino fall
         * Also, at each thousandth of score the tetromino fall faster by
         * reducing the amount of 'delay'
         */
        if (tick % delay == 0) {
            tick = 0;
            
            if (score && score % 1000 == 0) {
                delay -= (delay > 7500) ? (1000 * (score / 1000)) : (0);
            }

            moveTetroDown (landed, currentTetro);
        }
        
        /* During the game, whenever user input, these functions will be
         * executed, in the order of checkCollision() -> move()/rotate(). Keys
         * can be set when the game has not been started.
         */
        int input = wgetch (gameArea->window);
        switch (input) {
            case KEY_DOWN:
            case 'S':
            case 's':
            case 'J':
            case 'j':
                moveTetroDown (landed, currentTetro);
                break;

            case ' ':
                hardDropTetro (landed, currentTetro);
                break;

            case KEY_UP:
            case 'W':
            case 'w':
            case 'K':
            case 'k':
                rotateTetro (landed, currentTetro);
                break;

            case KEY_LEFT:
            case 'A':
            case 'a':
            case 'H':
            case 'h':
                moveTetroLeft (landed, currentTetro);
                break;

            case KEY_RIGHT:
            case 'D':
            case 'd':
            case 'L':
            case 'l':
                moveTetroRight (landed, currentTetro);
                break;

            default:
                break;
        }
    }

    /* Erase the windows created to make an effect of clearing the screen, and
     * delete the data structures associated with them
     */
    werase (scoreArea->window);
    werase (gameArea->window);
    werase (keyhintArea->window);
    wnoutrefresh (scoreArea->window);
    wnoutrefresh (gameArea->window);
    wnoutrefresh (keyhintArea->window);
    doupdate ();

    delwin (scoreArea->window);
    delwin (gameArea->window);
    delwin (keyhintArea->window);

    displayGameOverInfo (score);

    endwin ();
    free (scoreArea);
    free (gameArea);
    free (keyhintArea);

    scoreArea = gameArea = keyhintArea = NULL;
}
