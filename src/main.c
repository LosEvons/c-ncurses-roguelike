#include "rogue.h"

int main ()
{
    int ch;
    Position * newPosition;

    Level * game_map;

    screenSetUp();

    game_map = createLevel(1);

    while((ch = getch()) != 'q')
    {
        newPosition = handleInput(ch, game_map->player);
        checkPosition(newPosition, game_map);
        moveMonsters(game_map);
        move(game_map->player->position->y, game_map->player->position->x);
    }
    endwin();

    return 0;
}
