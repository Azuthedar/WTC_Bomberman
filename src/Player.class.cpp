#include <Player.class.hpp>

Player::Player()
{
	this->_xPos = (GRID_X * MAP_X) / 2;
	this->_yPos = (GRID_Y * MAP_Y) / 2;

	this->init();
	return ;
}

Player::Player(int x, int y)
{
	this->_xPos = x;
	this->_yPos = y;
	this->init();
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

void	Player::init()
{
	this->_lives = 3;
	this->_score = 0;

	this->_isCollide = false;
	this->_pickupPowerup = false;
	this->_isMoving = false;


	this->_speed = 2;
	this->_bombRange = 1;
	this->_bombs = 3;

/* 	this->_bomb[0].setBombAmount(this->_totalBombAmount);
	this->_bomb[0].setBombRange(this->_bombRange ); */

	this->_keyMoveDown = sf::Keyboard::Down;
	this->_keyMoveRight = sf::Keyboard::Right;
	this->_keyMoveUp = sf::Keyboard::Up;
	this->_keyMoveLeft = sf::Keyboard::Left;
	this->_keyPlaceBomb = sf::Keyboard::Space;
	return ;
}

void	Player::movement(std::vector<Wall> & wall)
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
			this->_typePowerup = POW_SPEED;
			this->_pickupPowerup = true;
		}
		if (sf::Keyboard::isKeyPressed(this->_keyPlaceBomb))
		{
			if (this->_bombs > 0 && !this->isBombThere(this->_xPos, this->_yPos))
			{
				this->_bombs--;
				this->getBombVector().push_back(Bomb(this->_xPos, this->_yPos));
			}
		}
	}
	if (this->_isMoving == true && !this->collision(wall))
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
	//	GRID BASED MOVEMENT
	if (this->_xPos % GRID_X == 0 && this->_yPos % GRID_Y == 0)
		this->_isMoving = false;
	this->respawn();
	this->pickupPowerUps();
}

bool	Player::collision(std::vector<Wall> & wall)
{
	this->_isCollide = false;
	for (size_t i = 0; i < wall.size(); i++)
	{
		switch (this->_dir) // ADD IN COLLISIONS FOR BOMBS
		{
			case LEFT:
				if (this->_xPos - GRID_X == wall[i].getXPos() && this->_yPos == wall[i].getYPos())
					this->_isCollide = true;
				break ;
			case RIGHT:
				if (this->_xPos + GRID_X == wall[i].getXPos() && this->_yPos == wall[i].getYPos())
					this->_isCollide = true;
				break ;
			case UP:
				if (this->_xPos == wall[i].getXPos() && this->_yPos - GRID_Y == wall[i].getYPos())
					this->_isCollide = true;
				break ;
			case DOWN:
				if (this->_xPos == wall[i].getXPos() && this->_yPos + GRID_Y == wall[i].getYPos())
					this->_isCollide = true;
				break ;
		}
	}
	return (this->_isCollide);
}

bool	Player::isBombThere(int x, int y)
{
	for (size_t i = 0; i < this->_bomb.size(); i++)
	{
		if (this->_bomb[i].getXPos() == x && this->_bomb[i].getYPos() == y)
		{
			return (true);
		}
	}
	return (false);
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
				for (size_t i = 0; i < this->_bomb.size(); i++)
					this->_bomb[i].setBombRange(this->_bombRange);
				break ;
			case POW_BOMBS:
				this->_bombs++;
				break ;
			case POW_SPEED:
				this->_speed += 1;
				break ;
			case POW_LIFE:
				this->_lives += 1;
		}
		this->_pickupPowerup = false;
	}
}

void	Player::evalScore()
{
	if (this->_typeScore == ENEMY)
		this->_score += 500;
	else if (this->_typeScore == LIVES && this->_lives > 0)
		this->_score = 2000 * this->_lives;
	else if (this->_typeScore == TIME_LEFT)
		this->_score = 100; // WILL CHANGE due to time_left not implemented yet
	else if (this->_typeScore == POWERUPS)
		this->_score += 50;
}

std::vector<Bomb> &		Player::getBombVector() {return (this->_bomb);}

int		Player::getBombs()
{
	return this->_bombs;
}