#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

enum eBlockType
{
	OPEN_TERRAIN = 0,
	SOLID_BLOCK,
	DESTRUCTIBLE_BLOCK,
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


#define GRID_X 48
#define GRID_Y 48
#define MAP_X 16
#define MAP_Y 16