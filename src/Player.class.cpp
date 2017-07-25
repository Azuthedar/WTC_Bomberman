#include <Player.class.hpp>

Player::Player()
{
	this->_lives = 3;
	this->_score = 0;
	this->_isCollide = false;
	this->_canPlaceBombs = false;
	return ;
}

Player::Player(Player const & src)
{
	*this = src;
	return ;
}

Player::~Player()
{
	this->_isDead = false;
	std::cout << "Player has been destroyed" << std::endl;
	return ;
}

void	Player::movement()
{
	/*
	*	X = 0 Y = 0 is at the top left of the screen
	*	If the DIR is UP	 	the yPos needs to decrease imitating moving UPWARDS
	*	If the DIR is DOWN		the yPos needs to increase to imitate moving DOWNWARDS
	*	If the DIR is LEFT		the xPos needs to decrease to imitate moving left
	*	If the DIR is RIGHT		the xPos needs to increase to imitate moving right
	*/	
	switch (this->_dir)
	{
		case UP:
			this->_yPos++;
			break ;
		case DOWN:
			this->_yPos--;
			break ;
		case LEFT:
			this->_xPos--;
			break ;
		case RIGHT:
			this->_xPos++;
			break ;
	}
}

void	Player::collision()
{
	this->_isCollide = true;
}