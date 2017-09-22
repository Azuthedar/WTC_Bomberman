#include "../include/Enemy.class.hpp"

Enemy::Enemy()
{
	this->_speed = std::rand() % 6 / 6 + 1;
	this->_type = static_cast<eEnemyType>(std::rand() % 2);
	this->_enemyMvTicker = 0;
	this->_followPlayer = false;
	this->_isDead = false;

	this->_xPos = 0;
	this->_yPos = 0;

	return ;
}

Enemy::Enemy(int x, int y)
{
	this->_speed = std::rand() % 8 + 1 / 6;
	this->_type = static_cast<eEnemyType>(std::rand() % 2);
	this->_enemyMvTicker = 0;
	this->_isDead = false;

	this->_xPos = x;
	this->_yPos = y;
	this->_spawnX = x;
	this->_spawnY = y;

	return ;
}


/*Enemy::Enemy(Enemy const & src)
{
	*this = src;
	return ;
}*/

Enemy::~Enemy()
{
	//std::cout << "Enemy has been destroyed" << std::endl;
	return ;
}

void 	Enemy::SnapMovement()
{
	if ((this->_xPos == this->_goal_x && this->_yPos == this->_goal_y && this->_enemyMvTicker <= 0) || this->_isCollide == true)
		this->_isMoving = false;
}

void	Enemy::movement(std::vector<Wall> & wall, std::vector<Enemy> & enemy, std::vector<Bomb> & bombVector, GLfloat &delta_time )
{

	if (this->_enemyMvTicker <= 0 && this->_isMoving == false)
	{
		this->_enemyMvTicker = std::rand() % ENEMY_MOVE_TICK + 1;
		this->_dir = static_cast<eMovementDir>(std::rand() % 4);
		while (this->checkWallAtPos(wall))
		{
			this->_dir = static_cast<eMovementDir>(std::rand() % 4);
		}
		this->_isMoving = true;
	}


	switch (this->_dir)
	{
			case LEFT :
				this->_goal_x = floor(this->_xPos + 1);
				this->_goal_y = this->_yPos;
				break ;
			case RIGHT :
				this->_goal_x = ceil(this->_xPos - 1);
				this->_goal_y = this->_yPos;
				break ;
			case UP :
				this->_goal_y = floor(this->_yPos + 1);
				this->_goal_x = this->_xPos;
				break ;
			case DOWN :
				this->_goal_y = ceil(this->_yPos - 1);
				this->_goal_x = this->_xPos;
				break ;
	}

	if (!this->collision(wall, enemy, bombVector))
	{
		if (this->_isMoving == true )
		{
			switch (this->_dir)
			{
				case LEFT :
						this->_xPos += this->_speed * delta_time;
						if (this->_xPos > this->_goal_x)
							this->_xPos = this->_goal_x;
					break ;
				case UP :
						this->_yPos += this->_speed * delta_time;
						if (this->_yPos > this->_goal_y)
							this->_yPos = this->_goal_y;
					break ;
				case DOWN :
						this->_yPos -= this->_speed * delta_time;
						if (this->_yPos < this->_goal_y)
							this->_yPos = this->_goal_y;
					break ;
				case RIGHT :
						this->_xPos -= this->_speed * delta_time;
						if (this->_xPos < this->_goal_x)
							this->_xPos = this->_goal_x;
					break ;
			}
		}
	}
	SnapMovement();

}

bool	Enemy::collision(std::vector<Wall> & wall, std::vector<Enemy> & enemy, std::vector<Bomb> & bombVector)
{
	this->_isCollide = false;
	for (size_t i = 0; i < wall.size(); i++)
	{
		switch (this->_dir) // Check the current position with every position of the wall
		{
			case LEFT:
				if ( this->_xPos + 1 == wall[i].getXPos() && this->_goal_y == wall[i].getYPos())
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

	for (size_t i = 0; i < enemy.size(); i++)
	{
		switch (this->_dir) // Check each individual Enemy position and compare it to its own
		{
			case LEFT:
				if ( this->_xPos + 1 == enemy[i].getXPos() && this->_goal_y == enemy[i].getYPos())
					this->_isCollide = true;
				break ;
			case RIGHT:
				if ( this->_yPos - 1 == enemy[i].getXPos() && this->_goal_y == enemy[i].getYPos())
					this->_isCollide = true;
				break ;
			case UP:
				if ( this->_goal_x == enemy[i].getXPos() && this->_yPos + 1 == enemy[i].getYPos())
					this->_isCollide = true;
				break ;
			case DOWN:
				if ( this->_goal_x == enemy[i].getXPos() && this->_yPos - 1 == enemy[i].getYPos())
					this->_isCollide = true;
				break ;
		}
	}

	for (size_t i = 0; i < bombVector.size(); i++)
	{
		switch (this->_dir) // Check each individual bomb position and compare it to its own
		{
			case LEFT:
				if ( this->_xPos + 1 == bombVector[i].getXPos() && this->_goal_y == bombVector[i].getYPos())
					this->_isCollide = true;
				break ;
			case RIGHT:
				if ( this->_xPos - 1 == bombVector[i].getXPos() && this->_goal_y == bombVector[i].getYPos())
					this->_isCollide = true;
				break ;
			case UP:
				if ( this->_goal_x == bombVector[i].getXPos() && this->_yPos + 1 == bombVector[i].getYPos())
					this->_isCollide = true;
				break ;
			case DOWN:
				if ( this->_goal_x == bombVector[i].getXPos() && this->_yPos - 1 == bombVector[i].getYPos())
					this->_isCollide = true;
				break ;
		}
		for (size_t j = 0; j < bombVector[i].getExplosionVector().size(); j++)
		{
			if (distance_to_point(this->_xPos, this->_yPos, bombVector[i].getExplosionVector()[j].getXPos(), bombVector[i].getExplosionVector()[j].getYPos()) < 1)
				this->_isDead = true;
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
int &	Enemy::getGoalX()		{return (this->_goal_x);}
int &	Enemy::getGoalY()		{return (this->_goal_y);}
eEnemyType & Enemy::getType() {return (this->_type);}


bool Enemy::checkWallAtPos(std::vector<Wall> & wall)
{
	if (this->_dir == LEFT)
	{
		for (size_t i = 0; i < wall.size(); i++)
		{
			if (this->_xPos + 1 == wall[i].getXPos() && this->_yPos == wall[i].getYPos())
				return (true);
		}
	}

	if (this->_dir == RIGHT)
	{
		for (size_t i = 0; i < wall.size(); i++)
		{
			if (this->_xPos - 1 == wall[i].getXPos() && this->_yPos == wall[i].getYPos())
				return (true);
		}
	}

	if (this->_dir == UP)
	{
		for (size_t i = 0; i < wall.size(); i++)
		{
			if (this->_yPos + 1 == wall[i].getYPos() && this->_xPos == wall[i].getXPos())
				return (true);
		}
	}

	if (this->_dir == DOWN)
	{
		for (size_t i = 0; i < wall.size(); i++)
		{
			if (this->_yPos - 1 == wall[i].getYPos() && this->_xPos == wall[i].getXPos())
				return (true);
		}
	}

	return (false);
}
