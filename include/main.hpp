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
#include "../Graphics_lib/Inc/Base.hpp"
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
	ENEMY,
	LIVES,
	POWERUPS,
	TIME_LEFT
};

#define MAP_X 18
#define MAP_Y 18
#define FIXED_FPS 60
#define BOMB_COOLDOWN 20
#define ENEMY_MOVE_TICK 4 * FIXED_FPS
#define MAP_TRANSITION_TIME 2 * FIXED_FPS
#define MAP_DURATION_TIME 2 * 60 * FIXED_FPS
#define BOMB_TIME 3 * FIXED_FPS
#define BOMB_TIME 3 * FIXED_FPS
#define DROP_PERCENTAGE 100