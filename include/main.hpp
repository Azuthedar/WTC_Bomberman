#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>

enum eBlockType
{
    OPEN_TERRAIN = 0,
    SOLID_BLOCKS,
    DESTRUCTABLE_BLOCKS
};

enum eMovementDir
{
    UP = 0,
    RIGHT,
    DOWN,
    LEFT
};

#define MAX_X 16
#define MAX_Y 16