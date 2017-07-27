#include <Player.class.hpp>

Player::Player()
{
	this->_lives = 3;
	this->_score = 0;
	this->_isCollide = false;
	this->_bombReady = false;
	this->_isMoving = false;
	this->_speed = 2;
	this->_xPos = (GRID_X * MAP_X) / 2;
	this->_yPos = (GRID_Y * MAP_Y) / 2;
	this->_keyMoveDown = sf::Keyboard::Down;
	this->_keyMoveRight = sf::Keyboard::Right;
	this->_keyMoveUp = sf::Keyboard::Up;
	this->_keyMoveLeft = sf::Keyboard::Left;
	return ;
}

Player::Player(Player const & src)
{
	*this = src;
	return ;
}

Player::~Player()
{
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
	if (this->_isMoving == false)
	{
		if (sf::Keyboard::isKeyPressed(this->_keyMoveRight))
		{
			this->_dir = RIGHT;
			this->_isMoving = true;
		}
		if (sf::Keyboard::isKeyPressed(this->_keyMoveLeft))
		{
			this->_dir = LEFT;
			this->_isMoving = true;
		}
		if (sf::Keyboard::isKeyPressed(this->_keyMoveUp))
		{
			this->_dir = UP;
			this->_isMoving = true;
		}
		if (sf::Keyboard::isKeyPressed(this->_keyMoveDown))
		{
			this->_dir = DOWN;
			this->_isMoving = true;
		}
	}

	if (this->_isMoving == true)
	{
		switch (this->_dir)
		{
			case LEFT :
				this->_xPos -= this->_speed;
				break ;
			case UP :
				this->_yPos -= this->_speed;
				break ;
			case DOWN :
				this->_yPos += this->_speed;
				break ;
			case RIGHT :
				this->_xPos += this->_speed;
				break ;
		}
	}

	if (this->_xPos % GRID_X == 0 && this->_yPos % GRID_Y == 0)
	{
		this->_isMoving = false;
	}
}

void	Player::collision()
{
	this->_isCollide = true;
}