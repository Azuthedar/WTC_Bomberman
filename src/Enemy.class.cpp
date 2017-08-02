#include <Enemy.class.hpp>

Enemy::Enemy()
{
	srand(time(NULL));
	this->_speed = rand() % 3 + 1;
	this->_enemyMvTicker = 0;

	this->_xPos = 0;
	this->_yPos = 0;
	return ;
}

Enemy::Enemy(int x, int y)
{
	srand(time(NULL));
	this->_speed = rand() % 3 + 1;
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

void	Enemy::movement(std::vector<Wall> & wall)
{
	if (this->_enemyMvTicker <= 0)
	{
		this->_enemyMvTicker = std::rand() % (4 * FIXED_FPS);
		this->_dir = static_cast<eMovementDir>(std::rand() % 4);
		this->_isMoving = true;
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
}

bool	Enemy::collision(std::vector<Wall> & wall)
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