#include "rogue.h"

Room ** mapSetUp()
{
    Room ** rooms;
    rooms = malloc(sizeof(Room)*6);

    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);

    rooms[1] = createRoom(2, 40, 6, 8);
    drawRoom(rooms[1]);

    rooms[2] = createRoom(10, 40, 6, 12);
    drawRoom(rooms[2]);

    connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);
    //connectDoors(rooms[1]->doors[2], rooms[0]->doors[0]); // why does this not work?
    connectDoors(rooms[1]->doors[1], rooms[0]->doors[0]);
    

    return rooms;
}

char ** saveLevelPositions()
{
    int x, y;

    int level_height = 25;
    int level_width = 100;

    char ** tiles;

    tiles = malloc(sizeof(char *) * level_height);

    for (y = 0; y < level_height; y++)
    {
        tiles[y] = malloc(sizeof(char *) * level_width);
        for(x = 0; x < level_width; x++)
        {
            tiles[y][x] = mvinch(y, x);
        }
    }

    return tiles;
}