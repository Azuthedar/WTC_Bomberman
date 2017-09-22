#include "../include/Explosion.class.hpp"

Explosion::Explosion()
{
    this->_xPos = 0;
    this->_yPos = 0;
}

Explosion::Explosion(int x, int y)
{
    this->_xPos = x;
    this->_yPos = y;
}

Explosion::~Explosion()
{
	return ;
}
