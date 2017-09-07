#include "../include/Gate.class.hpp"

Gate::Gate()
{
	this->_xPos = -1;
	this->_yPos = -1;
	this->_exists = false;
	this->_isLocked = true;
	return ;
}

Gate::Gate(int x, int y)
{
	this->_xPos = x;
	this->_yPos = y;
	this->_exists = false;
	this->_isLocked = true;

	return ;
}

Gate::~Gate()
{
	return ;
}

void	Gate::setExists(bool exists)	{this->_exists = exists;}
void	Gate::setIsLocked(bool isLocked)	{this->_isLocked = isLocked;}

bool &	Gate::getExists()			{return (this->_exists);}
bool &	Gate::getIsLocked()			{return (this->_isLocked);}