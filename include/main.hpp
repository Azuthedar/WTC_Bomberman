#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>

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