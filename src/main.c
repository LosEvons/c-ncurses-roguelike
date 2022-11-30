#include "rogue.h"

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

    connectDoors(rooms[1]->doors[2], rooms[0]->doors[0]);
    connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);


    return rooms;
}