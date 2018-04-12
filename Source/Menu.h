/*
 * File: Menu.h
 * Author: Hieu Do
 * Description: Declare function prototypes and include sufficient libaries'
 * headers for Menu.c
 */

#ifndef MENU_H

# include <ncurses.h>
# include "GamePlay.h"

typedef struct {
    int index;
    const char *entry[4];
    void (*func[3])(void);
} menuType;

menuType *createMenu (void);
void displayGameMenu (WINDOW *, menuType *);
void hoverNextEntry (menuType *, int);
void runMenu (void);

void showRecentScores (void);
void helpAndAbout (void);
void finish (void);

# define HOVER_UP   11
# define HOVER_DOWN 12

# define IN_MENU    14

# define MENU_H
#endif
