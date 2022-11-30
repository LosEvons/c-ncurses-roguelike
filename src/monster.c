#include "rogue.h"

int addMonsters(Level * level)
{
    int x;
    int max_monsters = 6;
    level->monsters = malloc(sizeof(Monster *) * max_monsters);
    level->numberOfMonsters = 0;

    for (x = 0; x < level->numberOfRooms; x++)
    {
        if (((rand() % 2) == 0) && (level->numberOfMonsters < max_monsters))
        {
            level->monsters[level->numberOfMonsters] = selectMonster(level->level);
            setStartingPosition(level->monsters[level->numberOfMonsters], level->rooms[x]);
            level->numberOfMonsters++;
        }
    }
}

Monster * selectMonster(int level)
{
    int monster;
    switch (level)
    {
        case 1:
        case 2:
        case 3:
            monster = (rand() % 2) + 1; // number between 1 & 2 (spider & goblin)
            break;
        case 4:
        case 5:
            monster = (rand() % 2) + 2; // number between 2 & 3 (goblin & troll)
            break;
        case 6:
            monster = 3;
            break;
    }

    switch (monster)
    {
        case 1: // spider
            return createMonster('X', 2, 1, 1, 1, 1);
        case 2: // goblin
            return createMonster('G', 5, 3, 1, 1, 2);
        case 3: // troll
            return createMonster('T', 15, 5, 1, 1, 1);
    }
}

/*
1 Spider
    symbol: X
    levels: 1-3
    health: 2
    attack: 1
    speed: 1
    defence: 1
    pathfinding: 1 (random)
2 Goblin
    symbol: G
    levels: 1-5
    health: 5
    attack: 3
    speed: 1
    defence: 1
    pathfinding: 2 (seeking)
3 Troll
    symbol: T
    levels: 4-6
    health: 15
    attack: 5
    speed: 1
    defence: 1
    pathfinding: 1 (random)
*/

Monster * createMonster(
    char symbol, int health, int attack, int speed, int defence, int pathfinding)
{
    Monster * newMonster;
    newMonster = malloc(sizeof(Monster));

    newMonster->symbol = symbol;
    newMonster->health = health;
    newMonster->attack = attack;
    newMonster->speed = speed;
    newMonster->defence = defence;
    newMonster->alive = 1;
    newMonster->pathfinding = pathfinding;

    sprintf(newMonster->string, "%c", newMonster->symbol);

    return newMonster;
}

int killMonster(Monster * monster)
{
    mvprintw(monster->position->y, monster->position->x, ".");
    monster->alive = 0;

    return 0;
}

int setStartingPosition(Monster * monster, Room * room)
{
    monster->position = malloc(sizeof(Position));

    monster->position->y = (rand() % (room->height - 2)) + room->position.y + 1;
    monster->position->x = (rand() % (room->width - 2)) + room->position.x + 1;

    mvprintw(monster->position->y, monster->position->x, monster->string);
}

int moveMonsters(Level * level)
{ // Process monster turns
    int x;
    for (x = 0; x < level->numberOfMonsters; x++)
    {
        if(level->monsters[x]->alive == 0)
            continue;

        mvprintw(level->monsters[x]->position->y, level->monsters[x]->position->x, ".");
        if (level->monsters[x]->pathfinding == 1)
        {
            pathfindingRandom(level->monsters[x]->position);
        }
        else {
            pathfindingSeek(level->monsters[x]->position, level->player->position);
        }
        mvprintw(level->monsters[x]->position->y, level->monsters[x]->position->x, level->monsters[x]->string);
    }
}

int pathfindingSeek(Position * start, Position * destination)
{
    if ((abs((start->x - 1) - destination->x) < abs(start->x - destination->x)) && (mvinch(start->y, start->x - 1) == '.'))
    {   // step left
        start->x = start->x - 1;
    }
    else if ((abs((start->x + 1) - destination->x) < abs(start->x - destination->x)) && (mvinch(start->y, start->x + 1) == '.'))
    {   // step right
        start->x = start->x + 1;
    }
    else if ((abs((start->y - 1) - destination->y) < abs(start->y - destination->y)) && (mvinch(start->y - 1, start->x) == '.'))
    {   // step up
        start->y = start->y - 1;
    }
    else if ((abs((start->y + 1) - destination->y) < abs(start->y - destination->y)) && (mvinch(start->y + 1, start->x) == '.'))
    {   // step down
        start->y = start->y + 1;
    }
    else
    {
        /* do nothing */
    }

    return 0;
}

int pathfindingRandom(Position * position)
{
    int random;
    random = rand() % 5;

    switch (random)
    {
        case 0: // step up
            if (mvinch(position->y - 1, position->x) == '.')
            {
                position->y = position->y - 1;
            }
            break;

        case 1: // step down
            if (mvinch(position->y + 1, position->x) == '.')
            {
                    position->y = position->y + 1;
            }
            break;

        case 2: // step left
            if (mvinch(position->y, position->x - 1) == '.')
            {
                position->x = position->x - 1;
            }
            break;

        case 3: // step right
            if (mvinch(position->y, position->x + 1) == '.')
            {
                position->x = position->x + 1;
            }
            break;

        case 4: // do nothing
            break;
    }

    return 0;
}

Monster * getMonsterAt(Position * position, Monster ** monsters)
{
    int x;
    for (x = 0; x < 6; x++)
    {
        if ((position->y == monsters[x]->position->y) && (position->x == monsters[x]->position->x))
        {
            return monsters[x];
        }
    }
    
    return NULL;
}