/*
 * File: Menu.c
 * Author: Hieu Do
 * Description: Display the main menu of the game. Hardcorded for Hetris.
 */

#include "Menu.h"

menuType *createMenu (void)
{
    menuType *menu = (menuType *)malloc (sizeof (menuType));
    
    menu->index = 0;
    menu->entry[0] = "    PLAY    ";
    menu->entry[1] = "   SCORES   ";
    menu->entry[2] = "HELP & ABOUT";
    menu->entry[3] = "    QUIT    ";
    menu->func[0] = runGame;
    menu->func[1] = showRecentScores;
    menu->func[2] = helpAndAbout;

    return menu;
}

void runMenu (void)
{
    initscr ();
    cbreak ();
    noecho ();
    curs_set (0);

    WINDOW *menuWin = newwin (10, 14, LINES / 2 - 4, COLS / 2 - 6);
    menuType *gameMenu = createMenu ();

    keypad (menuWin, TRUE);
    int running = TRUE;
    while (running) {
        displayGameMenu (menuWin, gameMenu);

        int input = wgetch (menuWin);
        switch (input) {
            case KEY_UP:
            case 'W':
            case 'w':
            case 'K':
            case 'k':
                hoverNextEntry (gameMenu, HOVER_UP);
                break;

            case KEY_DOWN:
            case 'S':
            case 's':
            case 'J':
            case 'j':
                hoverNextEntry (gameMenu, HOVER_DOWN);
                break;

            case '\n':
            case KEY_RIGHT:                
                if (gameMenu->index == 3) {
                    running = FALSE;
                }
                else {
                    gameMenu->func[gameMenu->index] ();
                }

                break;

            default:
                break;
        }
    }

    free (gameMenu);
    gameMenu = NULL;

    delwin (menuWin);
    menuWin = NULL;

    endwin ();
}

void hoverNextEntry (menuType *gameMenu, int direction)
{
    int curIndex = gameMenu->index;
    switch (direction) {
        case HOVER_UP:
            curIndex = (curIndex == 0) ? (3) : (curIndex - 1);
            break;
        case HOVER_DOWN:
            curIndex = (curIndex == 3) ? (0) : (curIndex + 1);
            break;
    }
    gameMenu->index = curIndex;
}

void helpAndAbout (void)
{
    endwin ();
    (void) system ("man ./HetrisManual.6");
    wrefresh (stdscr);
}

void showRecentScores (void)
{
    FILE *highscore = NULL;
    displayScoreRecords (highscore, IN_MENU);
}

void displayGameMenu (WINDOW *menuWin, menuType *gameMenu)
{
    werase (menuWin);
    mvwprintw (menuWin, 1, 0, "   HETRIS   ");

    for (int i = 0, row = 3; i < 4; i++, row++) {
        if (i == gameMenu->index) {
            wattron (menuWin, A_REVERSE);
            mvwprintw (menuWin, row, 0, "%s", gameMenu->entry[i]);
            wattroff (menuWin, A_REVERSE);
        }
        else {
            mvwprintw (menuWin, row, 0, "%s", gameMenu->entry[i]);
        }
    }
    wrefresh (menuWin);
}
