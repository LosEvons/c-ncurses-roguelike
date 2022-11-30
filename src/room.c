#include "rogue.h"

/* map divided into a 3x2 grid */
#define GRID_CELL_WIDTH LEVEL_WIDTH / 3
#define GRID_CELL_HEIGHT LEVEL_HEIGHT / 2

Room * createRoom(int grid)
{
    Room * newRoom;
    newRoom = malloc(sizeof(Room));

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
    newRoom->position.x += rand() % (GRID_CELL_WIDTH - newRoom->width);
    newRoom->position.y += rand() % (GRID_CELL_HEIGHT - newRoom->height);

    newRoom->doors = malloc(sizeof(Position*) * 4);

    // top door
    newRoom->doors[0] = malloc(sizeof(Position));
    newRoom->doors[0]->y = newRoom->position.y;
    newRoom->doors[0]->x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
    // left door
    newRoom->doors[1] = malloc(sizeof(Position));
    newRoom->doors[1]->y = rand() % (newRoom->height - 2) + newRoom->position.y + 1;
    newRoom->doors[1]->x = newRoom->position.x;
    // bottom door
    newRoom->doors[2] = malloc(sizeof(Position));
    newRoom->doors[2]->y = newRoom->position.y + newRoom->height;
    newRoom->doors[2]->x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
    // right door
    newRoom->doors[3] = malloc(sizeof(Position));
    newRoom->doors[3]->y = rand() % (newRoom->height - 2) + newRoom->position.y + 1;
    newRoom->doors[3]->x = newRoom->position.x + newRoom->width - 1;

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
    mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
    mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
    mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
    mvprintw(room->doors[3]->y, room->doors[3]->x, "+");

    return 0;
}

int connectDoors(Position * doorOne, Position * doorTwo)
{
    Position temp;
    Position previous;

    int count = 0;

    temp.x = doorOne->x;
    temp.y = doorOne->y;

    previous = temp;

    while (1)
    {
        if ((abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x - 1) == ' '))
        {// step left
            previous.x = temp.x;
            temp.x = temp.x - 1;
        }
        else if ((abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x + 1) == ' '))
        {// step right
            previous.x = temp.x;
            temp.x = temp.x + 1;
        }
        else if ((abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y - 1, temp.x) == ' '))
        {// step up
            previous.y = temp.y;
            temp.y = temp.y - 1;
        }
        else if ((abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y + 1, temp.x) == ' '))
        {// step down
            previous.y = temp.y;
            temp.y = temp.y + 1;
        } 
        else
        {
            if(count == 0)
            {
                temp = previous;
                count++;
                continue;
            }
            else {
                return 0;
            }
        }
        mvprintw(temp.y, temp.x, "#");
    }
    
    return 0;
}