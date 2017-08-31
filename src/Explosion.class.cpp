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

Explosion::Explosion(Explosion const & src)
{
	*this = src;
	return ;
}

Explosion::~Explosion()
{
	std::cout << "Explosion has been destroyed" << std::endl;
	return ;
}
