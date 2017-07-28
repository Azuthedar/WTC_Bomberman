#include <Bomb.class.hpp>

Bomb::Bomb()
{
	this->_totalTimer = 5 * FIXED_FPS;
	this->_currTimer = this->_totalTimer;
	this->_range = 1;
	return ;
}

Bomb::Bomb(int x, int y)
{
	this->_totalTimer = 5 * FIXED_FPS;
	this->_currTimer = this->_totalTimer;
	this->_xPos = x;
	this->_yPos = y;
	this->_range = 1;
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

bool	Bomb::explode()
{
	this->_currTimer--;
	std::cout << "Countdown: " << this->_currTimer << std::endl;
	if (this->_currTimer == 0)
	{
		this->_currTimer = this->_totalTimer;
		return (true);
	}
	return (false);
}

void	Bomb::setBombRange(int range)	{this->_range = range;}