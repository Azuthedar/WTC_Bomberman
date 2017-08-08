#pragma once

#include <AEntity.class.hpp>
#include <Bomb.class.hpp>

class Enemy : public AEntity
{
	public:

		Enemy();
		Enemy(int x, int y);
		Enemy(Enemy const & src);
		~Enemy();

		void		movement(std::vector<Wall> & wall, std::vector<Enemy> & enemy, AEntity & player, std::vector<Bomb> & bombVector);
		bool		collision(std::vector<Wall> & wall, std::vector<Enemy> & enemy, std::vector<Bomb> & bombVector);
		void		spawn();

		void		modifyEnemyMvTicker();

		void		setSpawnX(int x);
		void		setSpawnY(int y);

		int &		getSpawnX();
		int &		getSpawnY();
		int &		getGoalX();
		int &		getGoalY();

		sf::Sprite	sprite__;

	private:

		int			_enemyMvTicker;
		int			_goalX;
		int			_goalY;
		int			_spawnX;
		int			_spawnY;
		int			_speed;
		bool		_isMoving;
		bool		_followPlayer;
};