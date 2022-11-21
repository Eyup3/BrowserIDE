//
// Created by eyup on 21.11.22.
//

#include "ncurses.h"
int setupnc()
{
    initscr();

    raw();
    noecho();


    keypad(stdscr, 1);
}