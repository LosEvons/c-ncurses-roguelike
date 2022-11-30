#include "rogue.h"

Level * createLevel(int level)
{
    Level * newLevel;
    newLevel = malloc(sizeof(Level));

    newLevel->level = level;
    newLevel->numberOfRooms = 3;
    newLevel->rooms = roomSetUp();
    newLevel->tiles = saveLevelPositions();

    newLevel->player = playerSetUp();

    placePlayer(newLevel->rooms, newLevel->player);

    addMonsters(newLevel);
    
    return newLevel;
}

Room ** roomSetUp()
{
    int x;
    Room ** rooms;
    rooms = malloc(sizeof(Room)*MAX_ROOMS);

    for (x = 0; x < MAX_ROOMS; x++)
    {
        rooms[x] = createRoom(x);
        drawRoom(rooms[x]);
    }

    return rooms;
}

char ** saveLevelPositions()
{
    int x, y;
    char ** tiles;

    tiles = malloc(sizeof(char *) * LEVEL_HEIGHT);

    for (y = 0; y < LEVEL_HEIGHT; y++)
    {
        tiles[y] = malloc(sizeof(char *) * LEVEL_WIDTH);
        for(x = 0; x < LEVEL_WIDTH; x++)
        {
            tiles[y][x] = mvinch(y, x);
        }
    }

    return tiles;
}