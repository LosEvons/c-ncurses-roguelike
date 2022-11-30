#include "rogue.h"

int main ()
{
    int ch;
    Position * newPosition;

    Level * game_map;

    screenGetUp();

    game_map = createLevel(1);

    while((ch = getch()) != 'q')
    {
        newPosition = handleInput(ch, game_map->player);
        checkPosition(newPosition, game_map->player, game_map->tiles);
        moveMonsters(game_map);
        move(game_map->player->position->y, game_map->player->position->x);
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
