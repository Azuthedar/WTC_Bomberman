#include "../include/Gate.class.hpp"

Gate::Gate()
{
	this->_xPos = GRID_X * -1;
	this->_yPos = GRID_Y * -1;
	this->_exists = false;
	return ;
}

Gate::Gate(int x, int y)
{
	this->_xPos = x;
	this->_yPos = y;
	this->_exists = false;

	return ;
}

Gate::~Gate()
{
	return ;
}

void	Gate::setExists(bool exists)	{this->_exists = exists;}

bool &	Gate::getExists()			{return (this->_exists);}
