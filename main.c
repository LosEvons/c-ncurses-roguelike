// cc -o main main.c -lncurses

#include <curses.h>


int screenGetUp();
int mapSetUp();

int main () 
{
        screenGetUp();

        mapSetUp(); 

        getch();

        endwin();

        return 0;
}

int screenGetUp() 
{
    initscr();
    printw("Hello World!");
    noecho();
    refresh();

    return 0;
}

int mapSetUp()
{
    mvprintw(13, 13, "#------#");
    mvprintw(14, 13, "|......|");
    mvprintw(15, 13, "|......|");
    mvprintw(16, 13, "|......|");
    mvprintw(17, 13, "|......|");
    mvprintw(18, 13, "#------#");
}