#include "rogue.h"

/* map divided into a 3x2 grid */
#define GRID_CELL_WIDTH LEVEL_WIDTH / 3
#define GRID_CELL_HEIGHT LEVEL_HEIGHT / 2

Room * createRoom(int grid, int numberOfDoors)
{
    int i;
    Room * newRoom;
    newRoom = malloc(sizeof(Room));
    newRoom->numberOfDoors = numberOfDoors;

    switch (grid)
    {
        case 0:
            newRoom->position.x = 0;
            newRoom->position.y = 0;
            break;
        case 1:
            newRoom->position.x = GRID_CELL_WIDTH;
            newRoom->position.y = 0;
            break;
        case 2:
            newRoom->position.x = GRID_CELL_WIDTH * 2;
            newRoom->position.y = 0;
            break;
        case 3:
            newRoom->position.x = 0;
            newRoom->position.y = GRID_CELL_HEIGHT;
            break;
        case 4:
            newRoom->position.x = GRID_CELL_WIDTH;
            newRoom->position.y = GRID_CELL_HEIGHT;
            break;
        case 5:
            newRoom->position.x = GRID_CELL_WIDTH * 2;
            newRoom->position.y = GRID_CELL_HEIGHT;
            break;
    }

    newRoom->height = rand() % MAX_ROOM_HEIGHT + MIN_ROOM_HEIGHT; // max size 11
    newRoom->width = rand() % MAX_ROOM_WIDTH + MIN_ROOM_WIDTH; // max size 18

    /* offset */
    newRoom->position.x += rand() % (GRID_CELL_WIDTH - newRoom->width) + 1;
    newRoom->position.y += rand() % (GRID_CELL_HEIGHT - newRoom->height) + 1;

    newRoom->doors = malloc(sizeof(Door *) * numberOfDoors);

    for (i = 0; i < numberOfDoors; i++)
    {
        newRoom->doors[i] = malloc(sizeof(Door));
        newRoom->doors[i]->connected = 0;
    }

    // top door
    newRoom->doors[0]->position.y = newRoom->position.y;
    newRoom->doors[0]->position.x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
    // left door
    newRoom->doors[1]->position.y = rand() % (newRoom->height - 2) + newRoom->position.y + 1;
    newRoom->doors[1]->position.x = newRoom->position.x;
    // bottom door
    newRoom->doors[2]->position.y = newRoom->position.y + newRoom->height;
    newRoom->doors[2]->position.x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
    // right door
    newRoom->doors[3]->position.y = rand() % (newRoom->height - 2) + newRoom->position.y + 1;
    newRoom->doors[3]->position.x = newRoom->position.x + newRoom->width - 1;

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
    mvprintw(room->doors[0]->position.y, room->doors[0]->position.x, "+");
    mvprintw(room->doors[1]->position.y, room->doors[1]->position.x, "+");
    mvprintw(room->doors[2]->position.y, room->doors[2]->position.x, "+");
    mvprintw(room->doors[3]->position.y, room->doors[3]->position.x, "+");

    return 0;
}