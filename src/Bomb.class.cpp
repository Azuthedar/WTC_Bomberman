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

void Bomb::explode()
{
	std::cout << "ALLAHU AKBAR" << std::endl;
	this->_explosionVector.push_back(Explosion(this->_xPos, this->_yPos));
}

void	Bomb::modifyCurrTimer(int currTimer)		{this->_currTimer += currTimer;}
int &	Bomb::getCurrTimer()					{return this->_currTimer;}
void	Bomb::setBombRange(int range)		{this->_range = range;}
std::vector<Explosion> &	Bomb::getExplosionVector()	{return (this->_explosionVector);}