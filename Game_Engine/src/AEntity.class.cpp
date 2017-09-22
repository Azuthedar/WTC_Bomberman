#include "../include/AEntity.class.hpp"

AEntity::AEntity()
{
	// Initializing direction and pos (Will probably be changed in future
	// as spawn position will change)
	this->_dir = UP;
	this->_xPos = 0;
	this->_yPos = 0;
	this->_isDead = false;
	return ;
}

AEntity::AEntity(AEntity const & src)
{
	*this = src;
	return ;
}

AEntity::~AEntity()
{
	//std::cout << "AEntity has been destroyed" << std::endl;
	return ;
}

void	AEntity::setDir(eMovementDir dir)	{this->_dir = dir;}
void	AEntity::setXPos(int xPos)			{this->_xPos = xPos;}
void	AEntity::setYPos(int yPos)			{this->_yPos = yPos;}
void	AEntity::setIsDead(bool dead)		{this->_isDead = dead;}

eMovementDir AEntity::getDir() const		{return (this->_dir);}
float		AEntity::getXPos() const			{return (this->_xPos);}
float		AEntity::getYPos() const			{return (this->_yPos);}
float		AEntity::getZPos() const			{return (this->_zPos);}
bool		AEntity::getIsDead() const			{return (this->_isDead);}

AEntity &AEntity::operator=(AEntity const &rhs) {
    this->_dir = rhs._dir;
    this->_xPos = rhs._xPos;
    this->_yPos = rhs._yPos;
    this->_isCollide = rhs._isCollide;
    this->_isDead = rhs._isDead;

    return *this;
}


