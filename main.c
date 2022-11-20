/***RandomFunctions***/
void debugMode();
void updateTerminalInfo();



#include <ncurses.h>
#include "stdio.h"
#include "string.h"

#define ctrl(x) (x & 0x1F)


int curX, curY;
int terX, terY;
int run = 1;

char Buffer[5][100]; // links länge der Reihe

int setupnc()
{
    initscr();

    raw();
    noecho();


    keypad(stdscr, 1);
}
int handlekeyinput()
{
    int ch = wgetch(stdscr);

    if (33 <= ch && ch <= 126)
    {
        printw("%c",(char)ch);
        curX++;
    }
    switch (ch) {
        case KEY_UP:
            curY--;
            break;
        case KEY_DOWN:
            curY++;
            break;
        case KEY_LEFT:
            curX--;
            break;
        case KEY_RIGHT:
            curX++;
            break;
        case ctrl('c'):
            run = 0;
            break;
        case ctrl('d'):
            debugMode();
    }

    move(curY, curX);

}

int inputfile()
{
    int i = 0;
    FILE* fptr = fopen("../text.txt", "r");
    if(fptr == NULL) {printw("Kill");}
    char content[100];

    while(fgets(content, 100, fptr) != NULL)
    {
        for (int j = 0; j <100; ++j) {
            Buffer[i][j] = content[j];
        }
        i++;
    }


    fclose(fptr);
    for (int j = 0; j < 5; ++j) {
        printw("%s", Buffer[j]);

    }

}
/***main***/
int main()
{
    setupnc();


    inputfile();


    while(run)
    {
        updateTerminalInfo();

        handlekeyinput();


        refresh();
    }

    endwin();
}




void debugMode()
{
    while(run)
    {
        updateTerminalInfo();
        mvprintw(0, 0, "curX: %d\ncurY: %d", curX, curY);
        mvprintw(2, 0, "terX: %d\nterY: %d", terX, terY);



        move(curY, curX);
        int ch = wgetch(stdscr);

        switch (ch) {
            case KEY_UP:
                if(curY > 0) curY--;
                break;
            case KEY_DOWN:
                if(curY < terY) curY++;
                break;
            case KEY_LEFT:
                curX--;
                break;
            case KEY_RIGHT:
                curX++;
                break;
            case ctrl('c'):
                run = 0;
                break;
        }
        clear();
        refresh();
    }
}


void updateTerminalInfo()
{
    //Update Terminal struct
    getyx(stdscr, curY, curX);
    getmaxyx(stdscr, terY, terX);


}






