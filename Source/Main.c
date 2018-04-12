/*
 * File: Main.c
 * Author: Hieu Do
 * Description: Contains the main() function.
 */

#include <ncurses.h>
#include "GamePlay.h"
#include "Menu.h"

void initGame (void);
void finnishAndQuit (void);

int main (void)
{
    initGame ();
    finnishAndQuit ();

    return 0;
}

void initGame (void)
{
    initscr ();
    int maxWidth, maxHeight;
    getmaxyx (stdscr, maxHeight, maxWidth);
    if (maxWidth != MIN_SCREEN_WIDTH || maxHeight != MIN_SCREEN_HEIGHT) {
        endwin ();
        fprintf (stderr, "Current screen width  = %i\n", maxWidth);
        fprintf (stderr, "Current screen height = %i\n", maxHeight);
        fprintf (stderr, "Require exactly (W x H) = (%i x %i) to operate\n", 
                 MIN_SCREEN_WIDTH, MIN_SCREEN_HEIGHT);

        exit (EXIT_FAILURE);
    }
    else {
        endwin ();
        runMenu ();
    }
}

void finnishAndQuit ()
{
    initscr ();
    cbreak ();
    noecho ();

    WINDOW *finnish = newwin (0, 0, 0, 0);
    
    int height, width;
    getmaxyx (finnish, height, width);
    height /= 2;
    width = width / 2 - 3;
    
    mvwprintw (finnish, height, width, "Good bye!");
    wrefresh (finnish);

    halfdelay (6);
    wgetch (finnish);

    werase (finnish);
    delwin (finnish);
    endwin ();
}
