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
Room ** mapSetUp();
Player * playerSetUp();
int handleInput(int input, Player * player);
int playerMove(int y, int x, Player * player);
int checkPosition(int newY, int newX, Player * entity);

/* Room Functions */
Room * createRoom(int y, int x, int height, int width);
int drawRoom(Room * room);

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

Room ** mapSetUp()
{
    Room ** rooms;
    rooms = malloc(sizeof(Room)*6);

    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);

    rooms[1] = createRoom(2, 40, 6, 8);
    drawRoom(rooms[1]);

    rooms[2] = createRoom(10, 40, 6, 11);
    drawRoom(rooms[2]);

    return rooms;
}

Room * createRoom(int y, int x, int height, int width)
{
    Room * newRoom;
    newRoom = malloc(sizeof(Room));
    
    newRoom->yAnchor = y;
    newRoom->xAnchor = x;
    newRoom->height = height;
    newRoom->width = width;

    return newRoom;
}

int drawRoom(Room * room)
{
    int x;
    int y;

    // draw top and bottom
    for (x = room->xAnchor; x < room->xAnchor + room->width; x++)
    {
        mvprintw(room->yAnchor, x, "-"); // top
        mvprintw(room->yAnchor + room->height, x, "-"); // bottom
    }

    // draw floor and side walls
    for (y = room->yAnchor + 1; y < room->yAnchor + room->height; y++)
    {
        // draw side walls
        mvprintw(y, room->xAnchor, "|");
        mvprintw(y, room->xAnchor + room->width - 1, "|");
        for (x = room->xAnchor + 1; x < room->xAnchor + room->width - 1; x++)
        {
            mvprintw(y, x, ".");
        }
    }

    return 0;
}

Player * playerSetUp()
{
    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->yPosition = 14;
    newPlayer->xPosition = 14;
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