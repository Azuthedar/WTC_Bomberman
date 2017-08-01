#pragma once

#include <AEntity.class.hpp>

class Enemy : public AEntity
{
	public:

		Enemy();
		Enemy(int x, int y);
		Enemy(Enemy const & src);
		~Enemy();

		void		movement(std::vector<Wall> & wall);
		bool		collision(std::vector<Wall> & wall);
		void		spawn();

		void		modifyEnemyMvTicker();

		void		setSpawnX(int x);
		void		setSpawnY(int y);

		int &		getSpawnX();
		int &		getSpawnY();

		sf::Sprite	sprite__;

	private:

		int			_enemyMvTicker;
		int			_spawnX;
		int			_spawnY;
		int			_speed;
		bool		_isMoving;
};