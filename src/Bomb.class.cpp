#include "../include/Bomb.class.hpp"

Bomb::Bomb()
{
	this->_totalTimer = BOMB_TIME;
	this->_currTimer = this->_totalTimer;
	this->_range = 1;
	this->_exploded = false;
	return ;
}

Bomb::Bomb(int x, int y)
{
	this->_totalTimer = BOMB_TIME;
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

void Bomb::explode(int bombRange, std::vector<Wall> & wallVector, std::vector<Powerup> & powerupVector, Gate & gate)
{

	std::cout << "ALLAHU AKBAR" << std::endl;
	this->_exploded = true;
	this->_explosionVector.push_back(Explosion(this->_xPos, this->_yPos)); //Push Explosion On Default Spot
	//Loop and push explosions in relative direction.
	float temp_x = this->_xPos;
	float temp_y = this->_yPos;
	//Left
	for (int i = 0; i < bombRange; i++)
	{
		temp_x -= GRID_X;
		bool coll = false;
		for (size_t t = 0; t < wallVector.size(); t++)
		{
			int randomDrop = std::rand() % 100 + 1;
			if (temp_x == wallVector[t].getXPos() && temp_y == wallVector[t].getYPos())
			{
				coll = true;
				if (wallVector[t].getBlockType() == DESTRUCTIBLE_BLOCK)
				{
					if (randomDrop <= DROP_PERCENTAGE)
						powerupVector.push_back(Powerup(wallVector[t].getXPos(), wallVector[t].getYPos()));
					wallVector.erase(wallVector.begin() + t);
				}
				else if (wallVector[t].getBlockType() == GATE)
				{
					gate.setXPos(wallVector[t].getXPos());
					gate.setYPos(wallVector[t].getYPos());
					gate.setExists(true);
					wallVector.erase(wallVector.begin() + t);
				}
			}
		}
		if (coll == false)
		{
			this->_explosionVector.push_back(Explosion(temp_x, temp_y));
		}
		else
			break ;
	}

	temp_x = this->_xPos;
	temp_y = this->_yPos;
	//Right
	for (int i = 0; i < bombRange; i++)
	{
		temp_x += GRID_X;
		bool coll = false;
		for (size_t t = 0; t < wallVector.size(); t++)
		{
			int randomDrop = std::rand() % 100 + 1;
			if (temp_x == wallVector[t].getXPos() && temp_y == wallVector[t].getYPos())
			{
				coll = true;
				if (wallVector[t].getBlockType() == DESTRUCTIBLE_BLOCK)
				{
					if (randomDrop <= DROP_PERCENTAGE)
						powerupVector.push_back(Powerup(wallVector[t].getXPos(), wallVector[t].getYPos()));
					wallVector.erase(wallVector.begin() + t);
				}
				else if (wallVector[t].getBlockType() == GATE)
				{
					gate.setXPos(wallVector[t].getXPos());
					gate.setYPos(wallVector[t].getYPos());
					gate.setExists(true);
					wallVector.erase(wallVector.begin() + t);
				}
			}
		}
		if (coll == false)
		{
			this->_explosionVector.push_back(Explosion(temp_x, temp_y));
		}
		else
			break ;
	}

	temp_x = this->_xPos;
	temp_y = this->_yPos;
	//Down
	for (int i = 0; i < bombRange; i++)
	{
		temp_y += GRID_Y;
		bool coll = false;
		for (size_t t = 0; t < wallVector.size(); t++)
		{
			int randomDrop = std::rand() % 100 + 1;
			if (temp_x == wallVector[t].getXPos() && temp_y == wallVector[t].getYPos())
			{
				coll = true;
				if (wallVector[t].getBlockType() == DESTRUCTIBLE_BLOCK)
				{
					if (randomDrop <= DROP_PERCENTAGE)
						powerupVector.push_back(Powerup(wallVector[t].getXPos(), wallVector[t].getYPos()));
					wallVector.erase(wallVector.begin() + t);
				}
				else if (wallVector[t].getBlockType() == GATE)
				{
					gate.setXPos(wallVector[t].getXPos());
					gate.setYPos(wallVector[t].getYPos());
					gate.setExists(true);
					wallVector.erase(wallVector.begin() + t);
				}
			}
		}
		if (coll == false)
		{
			this->_explosionVector.push_back(Explosion(temp_x, temp_y));
		}
		else
			break ;
	}

	temp_x = this->_xPos;
	temp_y = this->_yPos;
	//Up
	for (int i = 0; i < bombRange; i++)
	{
		temp_y -= GRID_Y;
		bool coll = false;
		for (size_t t = 0; t < wallVector.size(); t++)
		{
			int randomDrop = std::rand() % 100 + 1;
			if (temp_x == wallVector[t].getXPos() && temp_y == wallVector[t].getYPos())
			{
				coll = true;
				if (wallVector[t].getBlockType() == DESTRUCTIBLE_BLOCK)
				{
					if (randomDrop <= DROP_PERCENTAGE)
						powerupVector.push_back(Powerup(wallVector[t].getXPos(), wallVector[t].getYPos()));
					wallVector.erase(wallVector.begin() + t);
				}
				else if (wallVector[t].getBlockType() == GATE)
				{
					gate.setXPos(wallVector[t].getXPos());
					gate.setYPos(wallVector[t].getYPos());
					gate.setExists(true);
					wallVector.erase(wallVector.begin() + t);
				}
			}
		}
		if (coll == false)
		{
			this->_explosionVector.push_back(Explosion(temp_x, temp_y));
		}
		else
			break ;
	}
}

void	Bomb::modifyCurrTimer(int currTimer)		{this->_currTimer += currTimer;}
void	Bomb::setBombRange(int range)				{this->_range = range;}
int &	Bomb::getCurrTimer()						{return this->_currTimer;}
bool &	Bomb::getExploded()							{return this->_exploded;}
std::vector<Explosion> &	Bomb::getExplosionVector()	{return (this->_explosionVector);}
