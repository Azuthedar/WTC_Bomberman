#include <Bomb.class.hpp>

Bomb::Bomb()
{
	this->_bombExplodeTimer = 5;
	this->_range = 1;
	this->_amount = 1;
	return ;
}

Bomb::Bomb(int x, int y)
{
	this->_xPos = x;
	this->_yPos = y;
	this->_bombExplodeTimer = 5;
	this->_range = 1;
	this->_amount = 1;
	return ;
}

Bomb::Bomb(Bomb const & src)
{
	*this = src;
	return ;
}

Bomb::~Bomb()
{
	std::cout << "Bomb has been destroyed" << std::endl;
	return ;
}