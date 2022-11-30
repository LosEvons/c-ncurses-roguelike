#include "rogue.h"

int main ()
{
    Player * player;
    int ch;
    Position * newPosition;

    Level * game_map;

    screenGetUp();

    game_map = createLevel(1);

    player = playerSetUp();

    while((ch = getch()) != 'q')
    {
        newPosition = handleInput(ch, player);
        checkPosition(newPosition, player, game_map->tiles);
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
