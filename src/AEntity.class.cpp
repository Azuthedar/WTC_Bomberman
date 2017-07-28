#include <AEntity.class.hpp>

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
	std::cout << "AEntity has been destroyed" << std::endl;
	return ;
}

void	AEntity::movement(std::vector<Wall> & wall)
{
	//TODO: Bombs - move only when touched
	if (wall.size())
		;
}

void	AEntity::setDir(eMovementDir dir)	{this->_dir = dir;}
void	AEntity::setXPos(int xPos)			{this->_xPos = xPos;}
void	AEntity::setYPos(int yPos)			{this->_yPos = yPos;}
void	AEntity::setIsDead(bool dead)		{this->_isDead = dead;}

eMovementDir AEntity::getDir() const		{return (this->_dir);}
int		AEntity::getXPos() const			{return (this->_xPos);}
int		AEntity::getYPos() const			{return (this->_yPos);}
bool	AEntity::getIsDead() const			{return (this->_isDead);}
