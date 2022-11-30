#ifndef ROGUE_H
#define ROGUE_H

#include <stdlib.h>
#include <curses.h>
#include <time.h>

typedef struct GameMap
{
    char ** tiles;
    int numberOfRooms;
    int numberOfMonsters;
    struct Room ** rooms;
    struct Monster ** monsters;
} GameMap;

typedef struct Position {
    int x;
    int y;
} Position;

typedef struct Room
{
    Position position;
    int height;
    int width;

    Position ** doors;

    //Monster ** monsters;
    //Item ** items;
} Room;

typedef struct Player
{
    Position position;
    int health;
} Player;

int screenGetUp();
/* Level/Map Functions*/
Room ** mapSetUp();
char ** saveLevelPositions();

/* Player Functions */
Player * playerSetUp();
Position * handleInput(int input, Player * player, char ** game_map);
int playerMove(Position * newPosition, Player * player, char ** game_map);
int checkPosition(Position * newPosition, Player * entity, char ** game_map);

/* Room Functions */
Room * createRoom(int y, int x, int height, int width);
int drawRoom(Room * room);
int connectDoors(Position * doorOne, Position * doorTwo);

#endif