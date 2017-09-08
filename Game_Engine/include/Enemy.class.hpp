#pragma once

#include "AEntity.class.hpp"
#include "Bomb.class.hpp"
#include "main.hpp"

class Enemy : public AEntity
{
	public:

		Enemy();
		Enemy(int x, int y);
		Enemy(Enemy const & src);
		~Enemy();

		void		movement(std::vector<Wall> & wall, AEntity & player, std::vector<Enemy> & enemy, std::vector<Bomb> & bombVector, GLfloat &delta_time );
		bool		collision(std::vector<Wall> & wall, std::vector<Enemy> & enemy, std::vector<Bomb> & bombVector);
		bool		checkWallAtPos(std::vector<Wall> & wall);
		void		spawn();

		void		modifyEnemyMvTicker();

		void		setSpawnX(int x);
		void		setSpawnY(int y);

		int &		getSpawnX();
		int &		getSpawnY();
		int &		getGoalX();
		int &		getGoalY();
		eEnemyType & getType();

		void SnapMovement( );

	private:

		int			_enemyMvTicker;
		int			_goal_x;
		int			_goal_y;
		int			_spawnX;
		int			_spawnY;
		float		_speed;
		bool		_isMoving;
		bool		_followPlayer;
		eEnemyType _type;
};
