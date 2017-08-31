#include "../include/Player.class.hpp"

Player::Player()
{
	this->_xPos = (MAP_X) / 2;
	this->_yPos = (MAP_Y) / 2;

	this->_goal_x = 0;
	this->_goal_y = 0;

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
	this->_hitOnce = false;


	this->_totalSpeed = 6.0f;
	this->_speed = this->_totalSpeed;
	this->_bombRange = 1;
	this->_bombs = 10;

	this->_placeBombTimer = 0;

	//this->_keyMoveDown = sf::Keyboard::Down;
	//this->_keyMoveRight = sf::Keyboard::Right;
	//this->_keyMoveUp = sf::Keyboard::Up;
	//this->_keyMoveLeft = sf::Keyboard::Left;
	//this->_keyPlaceBomb = sf::Keyboard::Space;
	return ;
}

void	Player::input( GLFWwindow *window )
{
	if ( this->_isMoving == false )
	{
		if (glfwGetKey( window, GLFW_KEY_A)) // left
		{
			this->_dir = LEFT;
			this->_isMoving = true;
			this->_hitOnce = false;
			
			this->_goal_x = floor(this->_xPos + 1);
			this->_goal_y = this->_yPos;
		}
		else if (glfwGetKey( window, GLFW_KEY_D)) // right
		{
			this->_dir = RIGHT;
			this->_isMoving = true;
			this->_hitOnce = false;

			this->_goal_x = ceil(this->_xPos - 1);
			this->_goal_y = this->_yPos;
		}
		else if (glfwGetKey( window, GLFW_KEY_S)) // down
		{
			this->_dir = DOWN;
			this->_isMoving = true;
			this->_hitOnce = false;

			this->_goal_y = ceil(this->_yPos - 1);
			this->_goal_x = this->_xPos;
		}
		else if (glfwGetKey( window, GLFW_KEY_W)) // up
		{
			this->_dir = UP;
			this->_isMoving = true;
			this->_hitOnce = false;

			this->_goal_y = floor(this->_yPos + 1);
			this->_goal_x = this->_xPos;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		if (this->_bombs > 0 && this->_placeBombTimer <= 0)
		{
			int		place_x = this->_xPos; //Where it should place the bombs
			int		place_y = this->_yPos; //Where it should place the bombs

			checkBombPlacement(place_x, place_y);

			if (!this->isBombThere(place_x, place_y))
			{
				this->_bombs--;
				this->getBombVector().push_back(Bomb(place_x, place_y));
				this->_placeBombTimer = BOMB_COOLDOWN;
			}
		}
	}
}

void 	Player::SnapMovement( )
{
	if (this->_goal_x == this->_xPos && this->_goal_y == this->_yPos)
		this->_isMoving = false;
}

void	Player::movement(std::vector<Wall> & wall, std::vector<Enemy> & enemy, std::vector<Powerup> & powerupVector, GLfloat &deltaTime )
{
	/*
	*	X = 0 Y = 0 is at the top left of the screen
	*	If the DIR is UP	 	the yPos needs to decrease imitating moving UPWARDS
	*	If the DIR is DOWN		the yPos needs to increase to imitate moving DOWNWARDS
	*	If the DIR is LEFT		the xPos needs to decrease to imitate moving left
	*	If the DIR is RIGHT		the xPos needs to increase to imitate moving right
	*/
	if (this->_isMoving == true)
	{
		if (!this->collision(wall, enemy, powerupVector))
		{
			switch (this->_dir)
			{
				case LEFT :
						this->_xPos += this->_speed * deltaTime;
						if (this->_xPos > this->_goal_x)
							this->_xPos = this->_goal_x;
					break ;
				case UP :
						this->_yPos += this->_speed * deltaTime;
						if (this->_yPos > this->_goal_y)
						this->_yPos = this->_goal_y;
					break ;
				case DOWN :
						this->_yPos -= this->_speed * deltaTime;
						if (this->_yPos < this->_goal_y)
						this->_yPos = this->_goal_y;
					break ;
				case RIGHT :
						this->_xPos -= this->_speed * deltaTime;
						if (this->_xPos < this->_goal_x)
						this->_xPos = this->_goal_x;
					break ;
			}
		}
	}
	SnapMovement();
	if (this->collision(wall, enemy, powerupVector))
		this->_isMoving = false;
}

bool	Player::collision(std::vector<Wall> & wall, std::vector<Enemy> & enemy, std::vector<Powerup> & powerupVector)
{
	this->_isCollide = false;
	
	for (size_t i = 0; i < wall.size(); i++)
	{
		switch (this->_dir) // ADD IN COLLISIONS FOR BOMBS
		{
			case LEFT:
				if (this->_xPos + 1 == wall[i].getXPos() && this->_goal_y == wall[i].getYPos())
					this->_isCollide = true;
				break ;
			case RIGHT:
				if ( this->_xPos - 1 == wall[i].getXPos() && this->_goal_y == wall[i].getYPos())
					this->_isCollide = true;
				break ;
			case UP:
				if ( this->_goal_x == wall[i].getXPos() && this->_yPos + 1 == wall[i].getYPos())
					this->_isCollide = true;
				break ;
			case DOWN:
				if ( this->_goal_x == wall[i].getXPos() && this->_yPos - 1 == wall[i].getYPos())
					this->_isCollide = true;
				break ;
		}
	}

	for (size_t i = 0; i < this->_bomb.size(); i++)
	{
		switch (this->_dir) // ADD IN COLLISIONS FOR BOMBS
		{
			case LEFT:
				if ( this->_xPos + 1 == this->_bomb[i].getXPos() && this->_goal_y == this->_bomb[i].getYPos())
					this->_isCollide = true;
				break ;
			case RIGHT:
				if ( this->_goal_x == this->_bomb[i].getXPos() && this->_goal_y == this->_bomb[i].getYPos())
					this->_isCollide = true;
				break ;
			case UP:
				if ( this->_goal_x == this->_bomb[i].getXPos() && this->_goal_y == this->_bomb[i].getYPos())
					this->_isCollide = true;
				break ;
			case DOWN:
				if ( this->_goal_x == this->_bomb[i].getXPos() && this->_goal_y == this->_bomb[i].getYPos())
					this->_isCollide = true;
				break ;
		}
	}

	for (size_t i = 0; i < powerupVector.size(); i++) // Checks player position and powerup vector
	{
		if (this->_goal_x == powerupVector[i].getXPos() && this->_goal_y == powerupVector[i].getYPos())
		{
			this->_pickupPowerup = true;
			this->pickupPowerUps(powerupVector[i].getTypePowerup());
			powerupVector.erase(powerupVector.begin() + i); // Erase from array after picked up
		}

	}
	if (!this->_hitOnce) // Check if the player has already been hit by the explosion
	{
		for (size_t i = 0; i < this->_bomb.size(); i++)
		{
			for (size_t j = 0; j < this->_bomb[i].getExplosionVector().size(); j++)
			{
				if (distance_to_point( this->_xPos, this->_yPos, this->_bomb[i].getExplosionVector()[j].getXPos(), this->_bomb[i].getExplosionVector()[j].getYPos()) < 1 )
				{
					this->_hitOnce = true;
					this->_isDead = true;
					this->respawn();
				}
			}
		}
	}

	for (size_t i = 0; i < enemy.size(); i++)
	{
		if (distance_to_point(this->_xPos, this->_yPos, enemy[i].getXPos(), enemy[i].getYPos()) < 1)
		{
			this->respawn();
			this->_isDead = true;
			enemy[i].spawn();
		}
	}

	return (this->_isCollide);
}

void	Player::checkBombPlacement(int place_x, int place_y)
{
	switch (this->_dir)
	{
		case	RIGHT :
			if (abs(this->_goal_x - this->_xPos) > 1 / 2)
				place_x = this->_goal_x - 1;
			else
				place_x = this->_goal_x;
			place_y = this->_yPos;
			break ;
		case	LEFT :
			if (abs(this->_goal_x - this->_xPos) > 1 / 2)
				place_x = this->_goal_x + 1;
			else
				place_x = this->_goal_x;
			place_y = this->_yPos;
			break ;
		case	UP:
			if (abs(this->_goal_y - this->_yPos) > 1 / 2)
				place_y = this->_goal_y + 1;
			else
				place_y = this->_goal_y;
			place_x = this->_xPos;
			break ;
		case	DOWN:
			if (abs(this->_goal_y - this->_yPos) > 1 / 2)
				place_y = this->_goal_y - 1;
			else
				place_y = this->_goal_y;
			place_x = this->_xPos;
			break ;
	}
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
	}
	this->_xPos = this->_spawnX;
	this->_yPos = this->_spawnY;
	this->_goal_x = this->_spawnX;
	this->_goal_y = this->_spawnY;

	this->_isDead = false;
}

void	Player::pickupPowerUps(ePowerups type)
{
	if (this->_pickupPowerup)
	{
		static int speedLevel = 1;
		static int rangeLevel = 1;
		static int bombLevel = 1;
		switch (type)
		{
			case POW_RANGE:
				if (rangeLevel < 10)
				{
					this->_bombRange += 1;
					for (size_t i = 0; i < this->_bomb.size(); i++)
						this->_bomb[i].setBombRange(this->_bombRange);
					rangeLevel++;
				}

				break ;
			case POW_BOMBS:
				if (bombLevel < 10)
				{
					this->_bombs++;
					bombLevel++;
				}
				break ;
			case POW_SPEED:
				if (speedLevel < 10)
				{
					do
					{
						this->_speed += 0.1f;
					}	while (std::remainderf(MAP_X, this->_speed) < 0.0);
					speedLevel++;
				}
				break ;
			case POW_LIFE:
				this->_lives += 1;
				break ;
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

void	Player::modifyBombs()					{this->_bombs += 1;}
void	Player::modifyPlaceBombTimer()			{this->_placeBombTimer -= 1;}

void	Player::setSpawnX(int spawnX)
{
	this->_spawnX = spawnX;
	this->_xPos = spawnX;
}

void	Player::setSpawnY(int spawnY)
{
	this->_spawnY = spawnY;
	this->_yPos = spawnY;
}

int	&	Player::getBombs()						{return (this->_bombs);}
int &	Player::getSpawnX()						{return (this->_spawnX);}
int &	Player::getSpawnY()						{return (this->_spawnY);}
int &	Player::getBombRange()					{return (this->_bombRange);}
std::vector<Bomb> &		Player::getBombVector() {return (this->_bomb);}
