#include <ncurses.h>
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "mynclib.h"

#define ctrl(x) (x & 0x1F)

#define BUFFERCOLUMN 100
#define BUFFERROW 5

typedef struct
{
    char Buffer[100];
    int length;
} Row;

typedef struct
{
    int curX, curY;
    int terX, terY;
    int run;

    Row lines[5]; //

} Terminal;


int handlekeyinput(Terminal* main)
{
    int ch = wgetch(stdscr);

    if (33 <= ch && ch <= 126)
    {
        printw("%c",(char)ch);
        main->curX++;
    }
    switch (ch) {
        case KEY_UP:
            main->curY--;
            break;
        case KEY_DOWN:
            main->curY++;
            break;
        case KEY_LEFT:
            main->curX--;
            break;
        case KEY_RIGHT:
            main->curX++;
            break;
        case ctrl('c'):
            main->run = 0;
            break;
    }

    move(main->curY, main->curX);

}

int inputfile(Terminal* main)
{
    int i = 0;
    FILE* fptr = fopen("../text.txt", "r");
    if(fptr == NULL) {printw("Kill");}
    char content[100];

    for (int j = 0; j < 100; ++j) {
        content[j] = '\0';
    }

    while(fgets(content, 100, fptr) != NULL)
    {
        for (int j = 0; j <100; ++j) {
            if(content[j] == '\0') { main->lines[i].length = j; }
            main->lines[i].Buffer[j] = content[j];
        }
        i++;
    }


    fclose(fptr);
    for (int j = 0; j < 5; ++j) {
        //printw("%s      length: %d\n", main->lines[j].Buffer, main->lines[j].length);

    }

}



void updateTerminalInfo(Terminal* main)
{
    //Update Terminal struct
    getyx(stdscr, main->curY, main->curX);
    getmaxyx(stdscr, main->terY, main->terX);


}


/***main***/
int main()
{
    Terminal main = {.run = 1};
    setupnc();


    inputfile(&main);


    while(main.run)
    {
        updateTerminalInfo(&main);

        handlekeyinput(&main);


        refresh();
    }

    endwin();
}



