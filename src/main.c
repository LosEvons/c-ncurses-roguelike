#include "rogue.h"

int main ()
{
    Player * player;
    int ch;
    Position * newPosition;

    char ** game_map;

    screenGetUp();

    mapSetUp(); 

    game_map = saveLevelPositions();

    player = playerSetUp();

    while((ch = getch()) != 'q')
    {
        newPosition = handleInput(ch, player, game_map);
        checkPosition(newPosition, player, game_map);
    }
    endwin();

    return 0;
}

int screenGetUp()
{
    initscr();
    printw("Hello World!");
    noecho();
    refresh();

    // random seed for map gen
    srand(time(NULL));

    return 0;
}
