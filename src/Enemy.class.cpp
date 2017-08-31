#include "../include/Enemy.class.hpp"

Enemy::Enemy()
{
	this->_speed = std::rand() % 3 + 1;
	this->_enemyMvTicker = 0;
	this->_followPlayer = false;
	this->_isDead = false;

	this->_xPos = 0;
	this->_yPos = 0;

	this->collide_left = false;
	this->collide_right = false;
	this->collide_up = false;
	this->collide_down = false;

	this->change_dir = true;

	return ;
}

Enemy::Enemy(int x, int y)
{
	this->_speed = std::rand() % 4 + 2;
	this->_enemyMvTicker = 0;
	this->_isDead = false;

	this->_xPos = x;
	this->_yPos = y;
	this->_spawnX = x;
	this->_spawnY = y;

	this->collide_left = false;
	this->collide_right = false;
	this->collide_up = false;
	this->collide_down = false;

	this->change_dir = true;

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

void 	Enemy::SnapMovement( )
{

	if ( this->_goal_x != 0 && this->_goal_y != 0)
	{
	    if (this->_dir == RIGHT)
	    {
	        if (this->_xPos <= (float)this->_goal_x)
	        {
	            this->_xPos = this->_goal_x;
	        	this->change_dir = true;
	        }
	    }
	    else if (this->_dir == LEFT)
	    {
	        if (this->_xPos >= (float)this->_goal_x)
	        {
				this->_xPos = this->_goal_x;
	            this->change_dir = true;
	        }
	    }
	    else if (this->_dir == UP)
	    {
	        if (this->_yPos >= (float)this->_goal_y)
	        {
	            this->_yPos = this->_goal_y;
	            this->change_dir = true;
	        }
	    }
	    else if (this->_dir == DOWN)
	    {
	        if (this->_yPos <= (float)this->_goal_y)
	        {
	            this->_yPos = this->_goal_y;
	            this->change_dir = true;
	        }
	    }
	}
	this->_isMoving = false;

	//std::cout << " INSNAP xPOS " <<  this->_xPos << " CHENGE DIIRII " << this->change_dir << " INSNAP yPOS " << this->_yPos << std::endl;

}

void	Enemy::movement(std::vector<Wall> & wall, AEntity & player, std::vector<Bomb> & bombVector, GLfloat &delta_time )
{
	if (abs(this->_xPos - player.getXPos()) <= 2  && abs(this->_yPos - player.getYPos()) <= 2 )
	{
		this->_followPlayer = true;
		this->_isMoving = true;
	}
	else
		this->_followPlayer = false;
	if (!this->_followPlayer)
	{
		if (this->_enemyMvTicker <= 0 && this->_isMoving == false && this->change_dir == true )
		{
			this->_enemyMvTicker = std::rand() % ENEMY_MOVE_TICK + 1;
			this->_dir = static_cast<eMovementDir>(std::rand() % 4);
			this->_isMoving = true;
		}
	}
	else
	{
		if (this->change_dir == true)
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
	}

	switch (this->_dir)
	{
		case LEFT :
			if (this->change_dir == true)
			{
				if ( this->_xPos + 1 < MAP_X )
					this->_goal_x = this->_xPos + 1;
				this->_goal_y = this->_yPos;
				this->change_dir = false;
			}
			break ;
		case RIGHT :
			if (this->change_dir == true)
			{
				if ( this->_xPos - 1 > 0 )
					this->_goal_x = this->_xPos - 1;
				this->_goal_y = this->_yPos;
				this->change_dir = false;
			}
			break ;
		case UP :
			if (this->change_dir == true)
			{
				if ( this->_yPos - 1 > 0 )
					this->_goal_y = this->_yPos - 1;
				this->_goal_x = this->_xPos;
				this->change_dir = false;
			}
			break ;
		case DOWN :
			if (this->change_dir == true)
			{
				if ( this->_yPos + 1 < MAP_Y )
					this->_goal_y = this->_yPos + 1;
				this->_goal_x = this->_xPos;
				this->change_dir = false;
			}
			break ;
	}

	this->collision(wall, bombVector);
	if (this->_isMoving == true )
	{
		switch (this->_dir)
		{
			case LEFT :
				if (!this->collide_left)
					this->_xPos += this->_speed * delta_time;
				break ;
			case UP :
				if (!this->collide_up)
					this->_yPos += this->_speed * delta_time;
				break ;
			case DOWN :
				if (!this->collide_down)
					this->_yPos -= this->_speed * delta_time;
				break ;
			case RIGHT :
				if (!this->collide_right)
					this->_xPos -= this->_speed * delta_time;
				break ;
		}
		SnapMovement();
	}

}

bool	Enemy::collision(std::vector<Wall> & wall, std::vector<Bomb> & bombVector)
{
	this->_isCollide = false;
	this->collide_left = false;
	this->collide_right = false;
	this->collide_up = false;
	this->collide_down = false;

	for (size_t i = 0; i < wall.size(); i++)
	{
		switch (this->_dir) // Check the current position with every position of the wall
		{
			case LEFT:
				if ( this->_goal_x == wall[i].getXPos() && this->_goal_y == wall[i].getYPos())
				{
					//std::cout << "COLOIDI L" << std::endl;
					this->collide_left = true;
					this->change_dir = true;
				}
				break ;
			case RIGHT:
				if ( this->_goal_x == wall[i].getXPos() && this->_goal_y == wall[i].getYPos())
				{
					//std::cout << "COLOIDI R" << std::endl;
					this->collide_right = true;
					this->change_dir = true;
				}
				break ;
			case UP:
				if ( this->_goal_x == wall[i].getXPos() && this->_goal_y == wall[i].getYPos())
				{
					//std::cout << "COLOIDI U" << std::endl;
					this->collide_up = true;
					this->change_dir = true;
				}
				break ;
			case DOWN:
				if ( this->_goal_x == wall[i].getXPos() && this->_goal_y == wall[i].getYPos())
				{
					this->collide_down = true;
					this->change_dir = true;
				}
				break ;
		}
	}

/*	for (size_t i = 0; i < enemy.size(); i++)
	{
		switch (this->_dir) // Check each individual Enemy position and compare it to its own
		{
			case LEFT:
				if ( this->_goal_x == enemy[i].getXPos() && this->_goal_y == enemy[i].getYPos())
				{
					//std::cout << "COLOIDI L" << std::endl;
					this->collide_left = true;
					this->change_dir = true;
				}
				break ;
			case RIGHT:
				if ( this->_goal_x == enemy[i].getXPos() && this->_goal_y == enemy[i].getYPos())
				{
					//std::cout << "COLOIDI R" << std::endl;
					this->collide_right = true;
					this->change_dir = true;
				}
				break ;
			case UP:
				if ( this->_goal_x == enemy[i].getXPos() && this->_goal_y == enemy[i].getYPos())
				{
					//std::cout << "COLOIDI U" << std::endl;
					this->collide_up = true;
					this->change_dir = true;
				}
				break ;
			case DOWN:
				if ( this->_goal_x == enemy[i].getXPos() && this->_goal_y == enemy[i].getYPos())
				{
					this->collide_down = true;
					this->change_dir = true;
				}
				break ;
		}
	}*/

	for (size_t i = 0; i < bombVector.size(); i++)
	{
		switch (this->_dir) // Check each individual bomb position and compare it to its own
		{
			case LEFT:
				if ( this->_goal_x == bombVector[i].getXPos() && this->_goal_y == bombVector[i].getYPos())
				{
					//std::cout << "COLOIDI L" << std::endl;
					this->collide_left = true;
					this->change_dir = true;
				}
				break ;
			case RIGHT:
				if ( this->_goal_x == bombVector[i].getXPos() && this->_goal_y == bombVector[i].getYPos())
				{
					//std::cout << "COLOIDI R" << std::endl;
					this->collide_right = true;
					this->change_dir = true;
				}
				break ;
			case UP:
				if ( this->_goal_x == bombVector[i].getXPos() && this->_goal_y == bombVector[i].getYPos())
				{
					//std::cout << "COLOIDI U" << std::endl;
					this->collide_up = true;
					this->change_dir = true;
				}
				break ;
			case DOWN:
				if ( this->_goal_x == bombVector[i].getXPos() && this->_goal_y == bombVector[i].getYPos())
				{
					this->collide_down = true;
					this->change_dir = true;
				}
				break ;
		}
		for (size_t j = 0; j < bombVector[i].getExplosionVector().size(); j++)
		{
			if (distance_to_point(this->_xPos, this->_yPos, bombVector[i].getExplosionVector()[j].getXPos(), bombVector[i].getExplosionVector()[j].getYPos()) < MAP_X)
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
