#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../../Graphics_lib/Inc/Base.hpp"
#include "Exception.class.hpp"

float	distance_to_point(float x1, float y1, float x2, float y2);

enum eBlockType
{
	OPEN_TERRAIN = 0,
	SOLID_BLOCK,
	DESTRUCTIBLE_BLOCK,
	ENEMY_BLOCK,
	GATE, //ON TOP OF GATE WILL CREATE DESTRUCTIBLE_BLOCK
	PLAYER
};

enum eMovementDir
{
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
};

enum eGamestate
{
	SPLASH_SCREEN = 0,
	MENU,
	GAME,
	LEVEL_SELECT,
	SETTINGS,
	LOAD_GAME,
	//  BONUS: TUTORIAL
	//  BONUS: MAP EDITOR
	CREDITS
};

enum ePowerups
{
	POW_RANGE = 0,
	POW_BOMBS,
	POW_SPEED,
	POW_LIFE
};

enum eScore
{
	ENEMY = 0,
	LIVES,
	POWERUPS,
	TIME_LEFT
};

enum eEnemyType
{
	BUG = 0,
	ROBOT
};

enum eConfig
{
	CNF_MAP = 1,
	CNF_BOMBLVL = 3,
	CNF_RANGELVL,
	CNF_SPEEDLVL,
	CNF_LIVES,
	CNF_RESOLUTION = 8,
	CNF_SOUNDLVL,
	CNF_KBUP = 11,
	CNF_KBLEFT,
	CNF_KBRIGHT,
	CNF_KBDOWN,
	CNF_KBPLACE,
	CNF_KBPAUSE
};

enum eSound
{
	SND_DEFAULT = 0,
	SND_FOOTSTEP,
	SND_DEATH,
	SND_EXPLOSION,
	SND_LVLCOMPLETE,
	SND_BOMBPLACE,
	SND_GAMEOVER
};

#define MAP_X 18
#define MAP_Y 18
#define FIXED_FPS 60
#define BOMB_COOLDOWN 20
#define ENEMY_MOVE_TICK 4 * FIXED_FPS
#define MAP_TRANSITION_TIME 2 * FIXED_FPS
#define MAP_DURATION_TIME 2 * 60 * FIXED_FPS
#define BOMB_TIME 2 * FIXED_FPS
#define DROP_PERCENTAGE 100
