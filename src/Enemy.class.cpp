#include <Enemy.class.hpp>

Enemy::Enemy()
{
	this->_speed = std::rand() % 3 + 1;;
	this->_enemyMvTicker = 0;
	this->_followPlayer = false;

	this->_xPos = 0;
	this->_yPos = 0;
	return ;
}

Enemy::Enemy(int x, int y)
{
	this->_speed = std::rand() % 3 + 1;
	this->_enemyMvTicker = 0;

	this->_xPos = x;
	this->_yPos = y;
	return ;
}


Enemy::Enemy(Enemy const & src)
{
	*this = src;
	return ;
}

Enemy::~Enemy()
{
	//std::cout << "Enemy has been destroyed" << std::endl;
	return ;
}

void	Enemy::movement(std::vector<Wall> & wall, std::vector<Enemy> & enemy, AEntity & player)
{
	if (abs(this->_xPos - player.getXPos()) <= 2 * GRID_X && abs(this->_yPos - player.getYPos()) <= 2 * GRID_Y)
	{
		this->_followPlayer = true;
		this->_isMoving = true;
	}
	else
		this->_followPlayer = false;
	if (!this->_followPlayer)
	{
		if (this->_enemyMvTicker <= 0 && this->_isMoving == false)
		{
			this->_enemyMvTicker = std::rand() % ENEMY_MOVE_TICK + 1;
			this->_dir = static_cast<eMovementDir>(std::rand() % 4);
			this->_isMoving = true;
		}
	}
	else 
	{
		if (player.getXPos() > this->_xPos)
			this->_dir = RIGHT;
		else if (player.getXPos() < this->_xPos)
			this->_dir = LEFT;
		else if (player.getYPos() < this->_yPos)
			this->_dir = UP;
		else if (player.getYPos() > this->_yPos)
			this->_dir = DOWN;
	}
	switch (this->_dir)
	{
		case LEFT :
			this->_goalX = this->_xPos - GRID_X;
			this->_goalY = this->_yPos;
			break ;
		case RIGHT :
			this->_goalX = this->_xPos + GRID_X;
			this->_goalY = this->_yPos;
			break ;
		case UP :
			this->_goalX = this->_xPos;
			this->_goalY = this->_yPos - GRID_Y;
			break ;
		case DOWN :
			this->_goalX = this->_xPos;
			this->_goalY = this->_yPos + GRID_Y;
			break ;
	}
	if (this->_isMoving == true && !this->collision(wall, enemy))
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

bool	Enemy::collision(std::vector<Wall> & wall, std::vector<Enemy> & enemy)
{
	this->_isCollide = false;
	for (size_t i = 0; i < wall.size(); i++)
	{
		switch (this->_dir) // Check the current position with every position of the wall
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
	for (size_t i = 0; i < enemy.size(); i++)
	{
		switch (this->_dir) // Check each individual Enemy position and compare it to its own
		{
			case LEFT:
				if (this->_xPos - GRID_X == enemy[i].getXPos() && this->_yPos == enemy[i].getYPos())
					this->_isCollide = true;
				break ;
			case RIGHT:
				if (this->_xPos + GRID_X == enemy[i].getXPos() && this->_yPos == enemy[i].getYPos())
					this->_isCollide = true;
				break ;
			case UP:
				if (this->_xPos == enemy[i].getXPos() && this->_yPos - GRID_Y == enemy[i].getYPos())
					this->_isCollide = true;
				break ;
			case DOWN:
				if (this->_xPos == enemy[i].getXPos() && this->_yPos + GRID_Y == enemy[i].getYPos())
					this->_isCollide = true;
				break ;
		}
	}
	return (this->_isCollide);
}

void	Enemy::spawn()
{
	this->_xPos = this->_spawnX;
	this->_yPos = this->_spawnY;
	this->_isDead = false;
}

void	Enemy::modifyEnemyMvTicker() {(this->_enemyMvTicker < 0) ? this->_enemyMvTicker = 0 : this->_enemyMvTicker--;}

void	Enemy::setSpawnX(int x) {this->_spawnX = x;}
void	Enemy::setSpawnY(int y) {this->_spawnY = y;}

int	&	Enemy::getSpawnX()		{return (this->_spawnX);}
int	&	Enemy::getSpawnY()		{return (this->_spawnY);}
int &	Enemy::getGoalX()		{return (this->_goalX);}
int &	Enemy::getGoalY()		{return (this->_goalY);}