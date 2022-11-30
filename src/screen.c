#include "rogue.h"

int screenSetUp()
{
    initscr();
    printw("Hello World!");
    noecho();
    refresh();

    // random seed for map gen
    srand(time(NULL));

    return 0;
}

int printGameHub(Level * level)
{
    

    return 0;
}