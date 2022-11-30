#ifndef ROGUE_H
#define ROGUE_H

#include <stdlib.h>
#include <curses.h>
#include <time.h>

typedef struct Level
{
    char ** tiles;
    int level;
    int numberOfRooms;
    int numberOfMonsters;
    struct Room ** rooms;
    struct Monster ** monsters;
    struct Player * player;
} Level;

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
    Position * position;
    int health;
    int attack;
} Player;

typedef struct Monster
{
    char string[2];
    char symbol;
    int health;
    int attack;
    int speed;
    int defence;
    int pathfinding;
    int alive;
    Position * position;
} Monster;

int screenSetUp();
/* Level/Map Functions*/
Level * createLevel();
Room ** roomSetUp();
char ** saveLevelPositions();

/* Player Functions */
Player * playerSetUp();
Position * handleInput(int input, Player * player);
int playerMove(Position * newPosition, Player * player, char ** game_map);
int checkPosition(Position * newPosition, Level * game_map);

/* Room Functions */
Room * createRoom(int y, int x, int height, int width);
int drawRoom(Room * room);
int connectDoors(Position * doorOne, Position * doorTwo);

/* Monster Functions */
int addMonsters(Level * level);
Monster * selectMonster(int level);
Monster * createMonster(char symbol, int health, int attack, int speed, int defence, int pathfinding);
int killMonster(Monster * monster);
int setStartingPosition(Monster * monster, Room * room);
int moveMonsters(Level * level);
int pathfindingSeek(Position * start, Position * destination);
int pathfindingRandom(Position * position);
Monster * getMonsterAt(Position * position, Monster ** monsters);

/* Combat Functions */
int combat(Player * player, Monster * monster, int order);

#endif