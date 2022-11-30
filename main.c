// cc -o main main.c -lncurses
#include <stdlib.h>
#include <curses.h>

#include <time.h>

typedef struct Position {
    int x;
    int y;
} Position;

typedef struct Room
{
    Position position;
    int height;
    int width;

    Position doors[4];

    //Monster ** monsters;
    //Item ** items;
} Room;

typedef struct Player
{
    Position position;
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
int connectDoors(Position doorOne, Position doorTwo);

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

    // random seed for map gen
    srand(time(NULL));

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

    connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);

    return rooms;
}

Room * createRoom(int y, int x, int height, int width)
{
    Room * newRoom;
    newRoom = malloc(sizeof(Room));
    
    newRoom->position.y = y;
    newRoom->position.x = x;
    newRoom->height = height;
    newRoom->width = width;

    // top door
    newRoom->doors[0].y = newRoom->position.y;
    newRoom->doors[0].x = rand() % (width - 2) + newRoom->position.x + 1;
    // left door
    newRoom->doors[1].y = rand() % (height - 2) + newRoom->position.y + 1;
    newRoom->doors[1].x = newRoom->position.x;
    // bottom door
    newRoom->doors[2].y = newRoom->position.y + height;
    newRoom->doors[2].x = rand() % (width - 2) + newRoom->position.x + 1;
    // right door
    newRoom->doors[3].y = rand() % (height - 2) + newRoom->position.y + 1;
    newRoom->doors[3].x = newRoom->position.x + width - 1;

    return newRoom;
}

int drawRoom(Room * room)
{
    int x;
    int y;

    // draw top and bottom
    for (x = room->position.x; x < room->position.x + room->width; x++)
    {
        mvprintw(room->position.y, x, "-"); // top
        mvprintw(room->position.y + room->height, x, "-"); // bottom
    }

    // draw floor and side walls
    for (y = room->position.y + 1; y < room->position.y + room->height; y++)
    {
        // draw side walls
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");
        for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++)
        {
            mvprintw(y, x, ".");
        }
    }

    // draw corners
    mvprintw(room->position.y, room->position.x, "O"); // top-left
    mvprintw(room->position.y, room->position.x + room->width - 1, "O"); // top-right
    mvprintw(room->position.y + room->height, room->position.x, "O"); //bottom-left
    mvprintw(room->position.y + room->height, room->position.x + room->width - 1, "O"); // bottom-right

    // draw doors
    mvprintw(room->doors[0].y, room->doors[0].x, "+");
    mvprintw(room->doors[1].y, room->doors[1].x, "+");
    mvprintw(room->doors[2].y, room->doors[2].x, "+");
    mvprintw(room->doors[3].y, room->doors[3].x, "+");

    return 0;
}

int connectDoors(Position doorOne, Position doorTwo)
{
    Position temp;

    temp.x = doorOne.x;
    temp.y = doorOne.y;

    while (1)
    {
        if ((abs((temp.x - 1) - doorTwo.x) < abs(temp.x - doorTwo.x)) && (mvinch(temp.y, temp.x - 1) == ' '))
        {// step left
            mvprintw(temp.y, temp.x - 1, "#");
            temp.x = temp.x - 1;
        }
        else if ((abs((temp.x + 1) - doorTwo.x) < abs(temp.x - doorTwo.x)) && (mvinch(temp.y, temp.x + 1) == ' '))
        {// step right
            mvprintw(temp.y, temp.x + 1, "#");
            temp.x = temp.x + 1;
        }
        else if ((abs((temp.y - 1) - doorTwo.y) < abs(temp.y - doorTwo.y)) && (mvinch(temp.y - 1, temp.x) == ' '))
        {// step up
            mvprintw(temp.y - 1, temp.x, "#");
            temp.y = temp.y - 1;
        }
        else if ((abs((temp.y + 1) - doorTwo.y) < abs(temp.y - doorTwo.y)) && (mvinch(temp.y -+1, temp.x) == ' '))
        {// step down
            mvprintw(temp.y + 1, temp.x, "#");
            temp.y = temp.y + 1;
        } 
        else
        {
            return 1; 
        }

        // getch();
    }
    
    return 0;
}

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