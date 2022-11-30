#include "rogue.h"

Level * createLevel(int level)
{
    Level * newLevel;
    newLevel = malloc(sizeof(Level));

    newLevel->level = level;
    newLevel->numberOfRooms = MAX_ROOMS;
    newLevel->rooms = roomSetUp();
    connectDoors(newLevel);
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
        rooms[x] = createRoom(x, 4);
        drawRoom(rooms[x]);
    }

    return rooms;
}

void connectDoors(Level * level)
{
    int i, j;
    int randomRoom, randomDoor;
    int count;

    for (i = 0; i < level->numberOfRooms; i++)
    {
        for (j = 0; j < level->rooms[i]->numberOfDoors; j++)
        {
            if (level->rooms[i]->doors[j]->connected == 1) // is current door already connected
                continue;

            count = 0;

            while (count < 2)
            {
                randomRoom = rand() % level->numberOfRooms;
                randomDoor = rand() % level->rooms[randomRoom]->numberOfDoors;

                if (level->rooms[randomRoom]->doors[randomDoor]->connected == 1 || randomRoom == i) // is random door already connected or in the same room
                {
                    count++;
                    continue;
                }
                pathFind(&level->rooms[randomRoom]->doors[randomDoor]->position, &level->rooms[i]->doors[j]->position);

                level->rooms[randomRoom]->doors[randomDoor]->connected = 1;
                level->rooms[i]->doors[j]->connected = 1;
                break;
            }

            
        }
    }
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