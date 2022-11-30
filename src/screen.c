#include "rogue.h"

int screenSetUp()
{
    initscr();
    noecho();
    refresh();

    // random seed for map gen
    srand(time(NULL));

    return 0;
}

int printGameHub(Level * level)
{
    mvprintw(25, 0, "    Level: %d", level->level);
    printw("    Gold: %d", level->player->gold);
    printw("    Hp: %d/%d", level->player->health, level->player->maxHealth);
    printw("    Attack: %d", level->player->attack);
    printw("    Exp: %d", level->player->exp);
    printw("     "); // To make sure the whole line is cleared despite changes in length

    return 0;
}