#include "../include/Powerup.class.hpp"

Powerup::Powerup()
{
	return ;
}

Powerup::Powerup(int x, int y)
{
	this->_xPos = x;
	this->_yPos = y;
	this->randomPowerup();
	return ;
}

Powerup::~Powerup()
{
	return ;
}

void      Powerup::randomPowerup()
{
	this->_typePowerup = static_cast<ePowerups>(std::rand() % 4);
}

ePowerups &   Powerup::getTypePowerup()   {return (this->_typePowerup);}
