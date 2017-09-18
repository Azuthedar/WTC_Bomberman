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
	this->_bombs = 1;

	this->_placeBombTimer = 0;

	this->_speedLevel = 1;
	this->_rangeLevel = 1;
	this->_bombLevel = 1;

	this->_KBmoveUp = GLFW_KEY_W;
	this->_KBmoveLeft = GLFW_KEY_A;
	this->_KBmoveRight = GLFW_KEY_D;
	this->_KBmoveDown = GLFW_KEY_S;
	this->_KBplaceBomb = GLFW_KEY_SPACE;
	this->_KBpause = GLFW_KEY_ESCAPE;

	return ;
}

void	Player::input( GLFWwindow *window )
{
	if ( this->_isMoving == false )
	{
		if (glfwGetKey( window, this->_KBmoveLeft)) // left
		{
			this->_dir = LEFT;
			this->_isMoving = true;
			this->_hitOnce = false;

			this->_goal_x = floor(this->_xPos + 1);
			this->_goal_y = this->_yPos;
		}
		else if (glfwGetKey( window, this->_KBmoveRight)) // right
		{
			this->_dir = RIGHT;
			this->_isMoving = true;
			this->_hitOnce = false;

			this->_goal_x = ceil(this->_xPos - 1);
			this->_goal_y = this->_yPos;
		}
		else if (glfwGetKey( window, this->_KBmoveDown)) // down
		{
			this->_dir = DOWN;
			this->_isMoving = true;
			this->_hitOnce = false;

			this->_goal_y = ceil(this->_yPos - 1);
			this->_goal_x = this->_xPos;
		}
		else if (glfwGetKey( window, this->_KBmoveUp)) // up
		{
			this->_dir = UP;
			this->_isMoving = true;
			this->_hitOnce = false;

			this->_goal_y = floor(this->_yPos + 1);
			this->_goal_x = this->_xPos;
		}
	}

	if (glfwGetKey(window, this->_KBplaceBomb))
	{
		if (this->_bombs > 0 && this->_placeBombTimer <= 0)
		{
			int		place_x = this->_xPos; //Where it should place the bombs
			int		place_y = this->_yPos; //Where it should place the bombs

			if (this->_isMoving)
				checkBombPlacement(place_x, place_y);

			if (!this->isBombThere(place_x, place_y))
			{
				this->_bombs--;
				this->getBombVector().push_back(Bomb(place_x, place_y));
				if (this->_soundEnum != SND_DEATH && this->_soundEnum != SND_GAMEOVER && this->_soundEnum != SND_LVLCOMPLETE &&
					this->_soundEnum != SND_GATEFOUND && this->_soundEnum != SND_GATEUNLOCKED)
					this->_soundEnum = SND_BOMBPLACE;
				this->_placeBombTimer = BOMB_COOLDOWN;
			}
		}
	}
	if (glfwGetKey(window, this->_KBpause))
	{
		// PAUSE LOGIC
	}
}

void 	Player::SnapMovement( )
{
	if ((this->_goal_x == this->_xPos && this->_goal_y == this->_yPos) || this->_isCollide)
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
	if (!this->collision(wall, enemy, powerupVector))
	{
		if (this->_isMoving == true)
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
			if (this->_soundEnum != SND_DEATH && this->_soundEnum != SND_POWERUP && this->_soundEnum != SND_BOMBPLACE && this->_soundEnum != SND_GAMEOVER)
				this->_soundEnum = SND_FOOTSTEP;
		}
	}
	SnapMovement();
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
			if (this->_soundEnum != SND_DEATH && this->_soundEnum != SND_GAMEOVER)
				this->_soundEnum = SND_POWERUP;
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
			this->_isDead = true;
			this->respawn();
			enemy[i].spawn();
		}
	}

	return (this->_isCollide);
}

void	Player::checkBombPlacement(int & place_x, int & place_y)
{
	switch (this->_dir)
	{
		case	RIGHT :
			place_x = this->_goal_x + 1;
			place_y = this->_yPos;
			break ;
		case	LEFT :
			place_x = this->_goal_x - 1;
			place_y = this->_yPos;
			break ;
		case	UP:
			place_y = this->_goal_y - 1;
			place_x = this->_xPos;
			break ;
		case	DOWN:
			place_y = this->_goal_y + 1;
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
		if(this->_lives != 0)
		{
			this->_soundEnum = SND_DEATH;
		}
		if (this->_lives <= 0)
		{
			this->_soundEnum = SND_GAMEOVER;
			std::cout << "You have died..." << std::endl;	//CHANGE GAMESTATE TO MENU
		}
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
		switch (type)
		{
			case POW_RANGE:
				if (this->_rangeLevel < 10)
				{
					this->_bombRange += 1;
					for (size_t i = 0; i < this->_bomb.size(); i++)
						this->_bomb[i].setBombRange(this->_bombRange);
					this->_rangeLevel++;
				}

				break ;
			case POW_BOMBS:
				if (this->_bombLevel < 10)
				{
					this->_bombs++;
					this->_bombLevel++;
				}
				break ;
			case POW_SPEED:
				if (this->_speedLevel < 10)
				{
					this->_speedLevel++;
					this->_speed = 6 * pow(1.0292f, this->_speedLevel);
				}
				break ;
			case POW_LIFE:
				if (this->_lives < 10)
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
void	Player::setSpeed(float speed)				{this->_speed = speed;}
void	Player::setBombs(int bombs)					{this->_bombs = bombs;}
void	Player::setBombRange(int bombRange)			{this->_bombRange = bombRange;}
void	Player::setSpeedLevel(int speedLevel)		{this->_speedLevel = speedLevel;}
void	Player::setRangeLevel(int rangeLevel)		{this->_rangeLevel = rangeLevel;}
void	Player::setBombLevel(int bombLevel)			{this->_bombLevel = bombLevel;}
void	Player::setLives(int lives)					{this->_lives = lives;}
void    Player::setKBMoveUp(int KBmoveUp)           {this->_KBmoveUp = KBmoveUp;}
void    Player::setKBMoveLeft(int KBmoveLeft)       {this->_KBmoveLeft = KBmoveLeft;}
void    Player::setKBMoveRight(int KBmoveRight)     {this->_KBmoveRight = KBmoveRight;}
void    Player::setKBMoveDown(int KBmoveDown)     	{this->_KBmoveDown = KBmoveDown;}
void    Player::setKBPlaceBomb(int KBplaceBomb)		{this->_KBplaceBomb = KBplaceBomb;}
void	Player::setKBPause(int KBpause)				{this->_KBpause = KBpause;}
void	Player::setSoundEnum(eSound val)			{this->_soundEnum = val;}


int	&	Player::getBombs()						{return (this->_bombs);}
int &	Player::getSpawnX()						{return (this->_spawnX);}
int &	Player::getSpawnY()						{return (this->_spawnY);}
int &	Player::getBombRange()					{return (this->_bombRange);}
int &	Player::getSpeedLevel()					{return (this->_bombLevel);}
int &	Player::getRangeLevel()					{return (this->_rangeLevel);}
int &	Player::getBombLevel()					{return (this->_bombLevel);}
int &	Player::getLives()						{return (this->_lives);}
int &	Player::getKBMoveUp()           		{return (this->_KBmoveUp);}
int &	Player::getKBMoveLeft()         		{return (this->_KBmoveLeft);}
int &	Player::getKBMoveRight()        		{return (this->_KBmoveRight);}
int &	Player::getKBMoveDown()         		{return (this->_KBmoveDown);}
int &	Player::getKBPlaceBomb()          		{return (this->_KBplaceBomb);}
int &	Player::getKBPause()					{return (this->_KBpause);}
eSound & Player::getSoundEnum()					{return (this->_soundEnum);}
std::vector<Bomb> &		Player::getBombVector() {return (this->_bomb);}
