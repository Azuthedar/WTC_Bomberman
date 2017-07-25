#include <AEntity.class.hpp>
#include <main.hpp>

AEntity::AEntity()
{
	this->_dir = 0;
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
	std::cout << "AEntity has been destroyed" << std::endl;
	return ;
}

void	AEntity::movement()
{
	this->_xPos++;
	this->_yPos++;
}

void	AEntity::collision()
{
	this->_isCollide = true;
}