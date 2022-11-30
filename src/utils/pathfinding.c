#include "rogue.h"
#include "utils.h"

void addPositionYX(int ** frontier, int frontierCount, int startY, int startX)
{
    frontier[frontierCount][0] = startY;
    frontier[frontierCount][1] = startX;
}

int checkMapPosition(int y, int x)
{
    char temp = mvinch(y, x);

    if (temp ==  '.' || temp == '|' || temp == '-' || temp == 'O')
        return 0;
    else
        return 1;
}

int addNeighbors(int ** frontier, int frontierCount, int *** cameFrom, int y, int x)
{
    // north
    if (y > 0 && cameFrom[y - 1][x][0] < 0 && checkMapPosition(y - 1, x))
    {
        addPositionYX(frontier, frontierCount, y - 1, x);
        frontierCount++;
        cameFrom[y - 1][x][0] = y;
        cameFrom[y - 1][x][1] = x;
    }

    // south
    if (y < (LEVEL_HEIGHT - 1) && cameFrom[y + 1][x][0] < 0 && checkMapPosition(y + 1,x))
    {
        addPositionYX(frontier, frontierCount, y + 1, x);
        frontierCount++;
        cameFrom[y + 1][x][0] = y;
        cameFrom[y + 1][x][1] = x;
    }

    // east
    if (x < (LEVEL_WIDTH - 1) && cameFrom[y][x + 1][0] < 0 && checkMapPosition(y, x + 1))
    {
        addPositionYX(frontier, frontierCount, y, x + 1);
        frontierCount++;
        cameFrom[y][x + 1][0] = y;
        cameFrom[y][x + 1][1] = x;
    }

    // west
    if (x > 0 && cameFrom[y][x - 1][0] < 0 && checkMapPosition(y, x - 1))
    {
        addPositionYX(frontier, frontierCount, y, x - 1);
        frontierCount++;
        cameFrom[y][x - 1][0] = y;
        cameFrom[y][x - 1][1] = x;
    }

    return frontierCount;
}

void pathFind(Position * start, Position * end)
{
    int i, j;
    int x, y;
    int tempY; // avoids overwriting y later on
    int ** frontier = malloc(sizeof(int*) * LEVEL_HEIGHT * LEVEL_WIDTH);
    int *** cameFrom = malloc(sizeof(int**) * LEVEL_HEIGHT);

    int frontierIndex = 0;
    int frontierCount = 0;

    for (i = 0; i < LEVEL_HEIGHT * LEVEL_WIDTH; i++)
    {
        frontier[i] = malloc(sizeof(int)*2);
    }

    for (i = 0; i < LEVEL_HEIGHT; i++)
    {
        cameFrom[i] = malloc(sizeof(int*)*LEVEL_WIDTH);
        for (j = 0; j < LEVEL_WIDTH; j++)
        {
            cameFrom[i][j] = malloc(sizeof(int)*2);
            cameFrom[i][j][0] = -1;
            cameFrom[i][j][1] = -1; 
        }
    }

    // add start position to cameFrom
    cameFrom[start->y][start->x][0] = -9;
    cameFrom[start->y][start->x][1] = -9;

    // add start position to frontier
    addPositionYX(frontier, frontierCount, start->y, start->x);
    frontierCount++;

    while (frontierIndex < frontierCount)
    {
        y = frontier[frontierIndex][0];
        x = frontier[frontierIndex][1];
        frontierIndex++;

        if (y == end->y && x == end->x)
        {
            break;
        }

        frontierCount = addNeighbors(frontier, frontierCount, cameFrom, y, x);
    }

    y = end->y;
    x = end->x;

    while (y != start->y || x != start->x)
    {
        tempY = y; // avoid overwriting y
        y = cameFrom[tempY][x][0];
        x = cameFrom[tempY][x][1];
        mvprintw(y, x, "+");
    }
}