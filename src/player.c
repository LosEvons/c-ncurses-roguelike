#include "rogue.h"

Player * playerSetUp()
{
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));
    newPlayer->position = malloc(sizeof(Position));

    newPlayer->position->y = 14;
    newPlayer->position->x = 14;
    newPlayer->health = 20;

    mvprintw(newPlayer->position->y, newPlayer->position->x, "@");
    move(newPlayer->position->y, newPlayer->position->x);

    return newPlayer;
}

Position * handleInput(int input, Player * player)
{
    Position * newPosition;
    newPosition = malloc(sizeof(Position));
    switch (input)
    {
        // move up
        case 'w':
        case 'W':
            newPosition->y = player->position->y - 1;
            newPosition->x = player->position->x;
            break;
        
        // move down
        case 'a':
        case 'A':
            newPosition->y = player->position->y;
            newPosition->x = player->position->x - 1;
            break;

        // move left
        case 's':
        case 'S':
            newPosition->y = player->position->y + 1;
            newPosition->x = player->position->x;
            break;

        // move right
        case 'd':
        case 'D':
            newPosition->y = player->position->y;
            newPosition->x = player->position->x + 1;
            break;

        // default
        default:
            break;
    }

    return newPosition;

}

int checkPosition(Position * newPosition, Player * player, char ** game_map)
{
    int space;
    switch(mvinch(newPosition->y, newPosition->x))
    {
        case '.':
        case '#':
        case '+':
            playerMove(newPosition, player, game_map);
            break;
        
        default:
            move(player->position->y, player->position->x);
            break;
    }
}

int playerMove(Position * newPosition, Player * player, char ** game_map)
{
    char buffer[3]; // Might need to be a pointer or sumtin

    sprintf(buffer, "%c", game_map[player->position->y][player->position->x]);

    mvprintw(player->position->y, player->position->x, buffer);

    player->position->y = newPosition->y;
    player->position->x = newPosition->x;

    mvprintw(player->position->y, player->position->x, "@");
    move(player->position->y, player->position->x);
}