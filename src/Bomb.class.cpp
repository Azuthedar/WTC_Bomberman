#include <Bomb.class.hpp>

Bomb::Bomb()
{
	this->_totalTimer = 5;
	this->_currTimer = this->_totalTimer;
	this->_range = 1;
	this->_amount = 1;
	return ;
}

Bomb::Bomb(int x, int y)
{
	this->_totalTimer = 5;
	this->_currTimer = this->_totalTimer;
	this->_xPos = x;
	this->_yPos = y;
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

void	Bomb::explode()
{
	
}

void	Bomb::setBombRange(int range)	{this->_range = range;}
void	Bomb::setBombAmount(int amount)	{this->_amount = amount;}