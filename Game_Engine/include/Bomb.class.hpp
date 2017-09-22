#pragma once

#include "main.hpp"
#include "AEntity.class.hpp"
#include "Explosion.class.hpp"
#include "Wall.class.hpp"
#include "Powerup.class.hpp"
#include "Gate.class.hpp"

class Bomb : public AEntity
{
	public:

		Bomb();
		Bomb(int x, int y);

	~Bomb();

		void	explode(int bombRange, std::vector<Wall> & wallVector, std::vector<Powerup> & powerupVector, Gate & gate);
		void	destroyExplosion(float deltaTime);


		void	modifyCurrTimer(int currTimer);
		void	modifyExplosionLifeTime(float deltaTime);
		void	modifyBombLifeTime(float  deltaTime);

		void setBombLifeTime(float _bombLifeTime);
		void	setBombRange(int range);

		int	&	getCurrTimer(void);
		float & getExplosionLifeTime();
		bool &	getExploded();
		std::vector<Explosion> &	getExplosionVector();
		float & getBombLifeTime();



private:

		int		_currTimer; // Explode timer will be on default added just in case for chain bombs exploding
		int		_totalTimer;
		float	_explosionLifeTime;
		float 	_bombLifeTime;
		int		_range;
		bool	_exploded;
		bool	_isCollide;


		std::vector<Explosion>		_explosionVector;
};
