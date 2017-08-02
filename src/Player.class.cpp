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

void	Player::input()
{
	if (this->_isMoving == false)
	{
		if (sf::Keyboard::isKeyPressed(this->_keyMoveRight))
		{
			this->_dir = RIGHT;
			this->_isMoving = true;
			this->_goal_x = this->_xPos + GRID_X;
			this->_goal_y = this->_yPos;
		}
		if (sf::Keyboard::isKeyPressed(this->_keyMoveLeft))
		{
			this->_dir = LEFT;
			this->_isMoving = true;
			this->_goal_x = this->_xPos - GRID_X;
			this->_goal_y = this->_yPos;
		}
		if (sf::Keyboard::isKeyPressed(this->_keyMoveUp))
		{
			this->_dir = UP;
			this->_isMoving = true;
			this->_goal_y = this->_yPos - GRID_Y;
			this->_goal_x = this->_xPos;
		}
		if (sf::Keyboard::isKeyPressed(this->_keyMoveDown))
		{
			this->_dir = DOWN;
			this->_isMoving = true;
			this->_goal_y = this->_yPos + GRID_X;
			this->_goal_x = this->_xPos;
		}
		// TEMP
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon))
		{
			this->_typePowerup = POW_SPEED;
			this->_pickupPowerup = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(this->_keyPlaceBomb))
	{
		if (this->_bombs > 0 && this->_placeBombTimer <= 0)
		{
			int		place_x = 0; //Where it should place the bombs
			int		place_y = 0; //Where it should place the bombs

			switch (this->_dir)
			{
				case	RIGHT :
					if (abs(this->_goal_x - this->_xPos) > GRID_X / 2)
						place_x = this->_goal_x - GRID_X;
					else
						place_x = this->_goal_x;
					place_y = this->_yPos;
					break ;
				case	LEFT :
					if (abs(this->_goal_x - this->_xPos) > GRID_X / 2)
						place_x = this->_goal_x + GRID_X;
					else
						place_x = this->_goal_x;
					place_y = this->_yPos;
					break ;
				case	UP:
					if (abs(this->_goal_y - this->_yPos) > GRID_Y / 2)
						place_y = this->_goal_y + GRID_Y;
					else
						place_y = this->_goal_y;
					place_x = this->_xPos;
					break ;
				case	DOWN:
					if (abs(this->_goal_y - this->_yPos) > GRID_Y / 2)
						place_y = this->_goal_y - GRID_Y;
					else
						place_y = this->_goal_y;
					place_x = this->_xPos;
					break ;
			}

			if (!this->isBombThere(place_x, place_y))
			{
				this->_bombs--;
				this->getBombVector().push_back(Bomb(place_x, place_y));
				this->_placeBombTimer = BOMB_COOLDOWN;
			}
		}
	}
}

void	Player::movement(std::vector<Wall> & wall, std::vector<Enemy> & enemy)
{
	/*
	*	X = 0 Y = 0 is at the top left of the screen
	*	If the DIR is UP	 	the yPos needs to decrease imitating moving UPWARDS
	*	If the DIR is DOWN		the yPos needs to increase to imitate moving DOWNWARDS
	*	If the DIR is LEFT		the xPos needs to decrease to imitate moving left
	*	If the DIR is RIGHT		the xPos needs to increase to imitate moving right
	*/
	if (!this->collision(wall, enemy))
	{
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
		
	}
	//	GRID BASED MOVEMENT
	if (this->_xPos % GRID_X == 0 && this->_yPos % GRID_Y == 0)
		this->_isMoving = false;
}

bool	Player::collision(std::vector<Wall> & wall, std::vector<Enemy> & enemy)
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

	for (size_t i = 0; i < this->_bomb.size(); i++)
	{
		switch (this->_dir) // ADD IN COLLISIONS FOR BOMBS
		{
			case LEFT:
				if (this->_xPos - GRID_X == this->_bomb[i].getXPos() && this->_yPos == this->_bomb[i].getYPos())
					this->_isCollide = true;
				break ;
			case RIGHT:
				if (this->_xPos + GRID_X == this->_bomb[i].getXPos() && this->_yPos == this->_bomb[i].getYPos())
					this->_isCollide = true;
				break ;
			case UP:
				if (this->_xPos == this->_bomb[i].getXPos() && this->_yPos - GRID_Y == this->_bomb[i].getYPos())
					this->_isCollide = true;
				break ;
			case DOWN:
				if (this->_xPos == this->_bomb[i].getXPos() && this->_yPos + GRID_Y == this->_bomb[i].getYPos())
					this->_isCollide = true;
				break ;
		}
	}
	for (size_t i = 0; i < enemy.size(); i++)
	{
		switch (this->_dir)
		{
			case LEFT :
				if ((this->_xPos - GRID_X == enemy[i].getXPos() || this->_xPos == enemy[i].getXPos()) && this->_yPos == enemy[i].getYPos())
					this->respawn();
				break ;
			case RIGHT :
				if ((this->_xPos + GRID_X == enemy[i].getXPos() || this->_xPos == enemy[i].getXPos()) && this->_yPos == enemy[i].getYPos())
					this->respawn();
				break ;
			case UP :
				if (this->_xPos == enemy[i].getXPos() && (this->_yPos - GRID_Y == enemy[i].getYPos() || this->_yPos == enemy[i].getYPos()))
					this->respawn();
				break ;
			case DOWN :
				if (this->_xPos == enemy[i].getXPos() && (this->_yPos + GRID_Y == enemy[i].getYPos() || this->_yPos == enemy[i].getYPos()))
					this->respawn();
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
	}
	this->_xPos = this->_spawnX;
	this->_yPos = this->_spawnY;
	this->_isDead = false;
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

void	Player::modifyBombs()					{this->_bombs += 1;}
void	Player::modifyPlaceBombTimer()			{this->_placeBombTimer -= 1;}

void	Player::setSpawnX(int spawnX)			{this->_spawnX = spawnX;}
void	Player::setSpawnY(int spawnY)			{this->_spawnY = spawnY;}

int	&	Player::getBombs()						{return (this->_bombs);}
int &	Player::getSpawnX()						{return (this->_spawnX);}
int &	Player::getSpawnY()						{return (this->_spawnY);}
std::vector<Bomb> &		Player::getBombVector() {return (this->_bomb);}