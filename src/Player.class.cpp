#include <Player.class.hpp>

Player::Player()
{
	this->_xPos = (GRID_X * MAP_X) / 2;
	this->_yPos = (GRID_Y * MAP_Y) / 2;
	this->_lives = 3;
	this->_score = 0;

	this->_isCollide = false;
	this->_bombReady = false;
	this->_pickupPowerup = false;
	this->_isMoving = false;

	this->_speed = 2;
	this->_bombRange = 1;
	this->_bombAmount = 1;

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
		// TEMP
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon))
		{
			this->_lives--;
			this->_isDead = true;
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
	this->collision();
	this->respawn();
}

void	Player::collision()
{
	//	Check collisions for outer walls
	if (this->_xPos % GRID_X == 0 && this->_yPos % GRID_Y == 0)
	{
		this->_isMoving = false;
	}
}

void	Player::respawn()
{
	if (this->_isDead)
	{
		this->_lives -= 1;
		if (this->_lives <= 0)
			std::cout << "You have died..." << std::endl;	//CHANGE GAMESTATE TO MENU
		/*
		*	Possibly if player reaches 0 lives, make a total score appear in the middle of the screen
		*	Which then fades out and takes the player back to the main menu or the start of the round.
		*/
		this->_xPos = (MAP_X * GRID_X) / 2;
		this->_yPos = (MAP_Y * GRID_Y) / 2;
		this->_isDead = false;
	}
}

void	Player::pickupPowerUps()
{
	if (this->_pickupPowerup)
	{
		switch (this->_typePowerup)
		{
			case POW_RANGE:
				this->_bombRange += 1;
				break ;
			case POW_BOMBS:
				this->_bombAmount += 1;
				break ;
			case POW_SPEED:
				this->_speed += 1;
				break ;
			case POW_LIFE:
				this->_lives += 1;
		}
	/*
	*	bomb.setBombRange(this->_bombRange);
	*	bomb.setBombAmount(this->_bombAmount);
	*/
		this->_pickupPowerup = false;
	}
}

void	Player::evalScore()
{
	if (this->_typeScore == ENEMY)
		this->_score += 1000;
	else if (this->_typeScore == LIVES && this->_lives > 0)
		this->_score = 2000 * this->_lives;
	else if (this->_typeScore == TIME_LEFT)
		this->_score = 100; // WILL CHANGE due to time_left not implemented yet
	else if (this->_typeScore == POWERUPS)
		this->_score += 50;
}