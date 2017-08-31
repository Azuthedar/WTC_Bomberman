#pragma once

#include "main.hpp"

class Wall
{
	public:

		Wall();
		Wall(int x, int y, eBlockType type);
		Wall(Wall const & src);
		~Wall();

		int     	getXPos() const;
		int     	getYPos() const;
		eBlockType	&getBlockType();

	private:

		int         _xPos;
		int         _yPos;
		eBlockType  _blockType;
};
