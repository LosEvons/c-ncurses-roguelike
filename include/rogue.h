#ifndef ROGUE_H
#define ROGUE_H

#include <stdlib.h>
#include <curses.h>
#include <time.h>

/* level parameters */
#define LEVEL_HEIGHT 25
#define LEVEL_WIDTH 100

/* room parameters */
#define MIN_ROOM_WIDTH 5
#define MIN_ROOM_HEIGHT 5
#define MAX_ROOM_WIDTH 14
#define MAX_ROOM_HEIGHT 7
#define MAX_ROOMS 6

/* entity parameters */
#define MAX_MONSTERS 6

/* typed structs */
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

    struct Door ** doors;
    int numberOfDoors;
} Room;

typedef struct Door
{
    Position position;
    int connected;
} Door;

typedef struct Player
{
    Position * position;
    int maxHealth;
    int health;
    int attack;
    int gold;
    int exp;
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
    int expValue;
    int goldValue;
    Position * position;
} Monster;

/* Screen Functions */
int screenSetUp();
int printGameHub(Level * level);

/* Level/Map Functions*/
Level * createLevel();
Room ** roomSetUp();
char ** saveLevelPositions();
void connectDoors(Level * level);

/* Player Functions */
Player * playerSetUp();
Position * handleInput(int input, Player * player);
int playerMove(Position * newPosition, Player * player, char ** game_map);
int checkPosition(Position * newPosition, Level * game_map);
int placePlayer(Room ** rooms, Player * player);

/* Room Functions */
Room * createRoom(int grid, int numberOfDoors);
int drawRoom(Room * room);

/* Monster Functions */
int addMonsters(Level * level);
Monster * selectMonster(int level);
Monster * createMonster(
    char symbol, int health, int attack, int speed, 
    int defence, int pathfinding, int expValue, int goldValue
    );
int killMonster(Monster * monster);
int setStartingPosition(Monster * monster, Room * room);
int moveMonsters(Level * level);
int pathfindingSeek(Position * start, Position * destination);
int pathfindingRandom(Position * position);
Monster * getMonsterAt(Position * position, Monster ** monsters);

/* Combat Functions */
int combat(Player * player, Monster * monster, int order);

#endif