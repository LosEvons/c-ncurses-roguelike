// cc -o main main.c -lncurses
#include <stdlib.h>
#include <curses.h>

typedef struct Room
{
    int yAnchor;
    int xAnchor;
    int height;
    int width;
    //Monster ** monsters;
    //Item ** items;
} Room;

typedef struct Player
{
    int xPosition;
    int yPosition;
    int health;
} Player;

int screenGetUp();
int mapSetUp();
Player * playerSetUp();
int handleInput(int input, Player * player);
int playerMove(int y, int x, Player * player);
int checkPosition(int newY, int newX, Player * entity);

int main ()
{
    Player * player;
    int ch;
    screenGetUp();

    mapSetUp(); 

    player = playerSetUp();

    while((ch = getch()) != 'q')
    {
        handleInput(ch, player);
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
    
    mvprintw(2, 40, "#------#");
    mvprintw(3, 40, "|......|");
    mvprintw(4, 40, "|......|");
    mvprintw(5, 40, "|......|");
    mvprintw(6, 40, "|......|");
    mvprintw(7, 40, "#------#");

    mvprintw(10, 40, "#----------#");
    mvprintw(11, 40, "|..........|");
    mvprintw(12, 40, "|..........|");
    mvprintw(13, 40, "|..........|");
    mvprintw(14, 40, "|..........|");
    mvprintw(15, 40, "#----------#");
}

Player * playerSetUp()
{
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));

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
            newY = player->yPosition - 1;
            newX = player->xPosition;
            break;
        
        // move down
        case 'a':
        case 'A':
            newY = player->yPosition;
            newX = player->xPosition - 1;
            break;

        // move left
        case 's':
        case 'S':
            newY = player->yPosition + 1;
            newX = player->xPosition;
            break;

        // move right
        case 'd':
        case 'D':
            newY = player->yPosition;
            newX = player->xPosition + 1;
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
            playerMove(newY, newX, player);
            break;
        
        default:
            move(player->yPosition, player->xPosition);
            break;
    }
}

int playerMove(int y, int x, Player * player)
{
    mvprintw(player->yPosition, player->xPosition, ".");

    player->yPosition = y;
    player->xPosition = x;

    mvprintw(player->yPosition, player->xPosition, "@");
    move(player->yPosition, player->xPosition);
}