#include "rogue.h"

Player * playerSetUp()
{
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->position.y = 14;
    newPlayer->position.x = 14;
    newPlayer->health = 20;

    playerMove(14, 14, newPlayer);

    return newPlayer;
}

int handleInput(int input, Player * player)
{
    int newY;
    int newX;
    switch (input)
    {
        // move up
        case 'w':
        case 'W':
            newY = player->position.y - 1;
            newX = player->position.x;
            break;
        
        // move down
        case 'a':
        case 'A':
            newY = player->position.y;
            newX = player->position.x - 1;
            break;

        // move left
        case 's':
        case 'S':
            newY = player->position.y + 1;
            newX = player->position.x;
            break;

        // move right
        case 'd':
        case 'D':
            newY = player->position.y;
            newX = player->position.x + 1;
            break;

        // default
        default:
            break;
    }

    checkPosition(newY, newX, player);

}

int checkPosition(int newY, int newX, Player * player)
{
    int space;
    switch(mvinch(newY, newX))
    {
        case '.':
        case '#':
        case '+':
            playerMove(newY, newX, player);
            break;
        
        default:
            move(player->position.y, player->position.x);
            break;
    }
}

int playerMove(int y, int x, Player * player)
{
    mvprintw(player->position.y, player->position.x, ".");

    player->position.y = y;
    player->position.x = x;

    mvprintw(player->position.y, player->position.x, "@");
    move(player->position.y, player->position.x);
}