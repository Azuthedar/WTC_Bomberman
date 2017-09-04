#include "../include/Wall.class.hpp"

Wall::Wall()
{
    this->_xPos = 0;
    this->_yPos = 0;
    this->_blockType = SOLID_BLOCK;
}

Wall::Wall(int x, int y, eBlockType type)
{
    this->_xPos = x;
    this->_yPos = y;
    this->_blockType = type;
}

Wall::Wall(Wall const & src)
{
	*this = src;
}

Wall::~Wall()
{
	//std::cout << "Wall has been destroyed" << std::endl;
	return ;
}

int		    Wall::getXPos() const			{return (this->_xPos);}
int		    Wall::getYPos() const			{return (this->_yPos);}
eBlockType  &Wall::getBlockType()            {return (this->_blockType);}
