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
		Bomb(Bomb const & src);
		~Bomb();

		void	explode(int bombRange, std::vector<Wall> & wallVector, std::vector<Powerup> & powerupVector, Gate & gate);

		void	setBombRange(int range);
		void	modifyCurrTimer(int currTimer);

		int	&	getCurrTimer(void);
		bool &	getExploded();
		std::vector<Explosion> &	getExplosionVector();

	private:

		int		_currTimer; // Explode timer will be on default added just in case for chain bombs exploding
		int		_totalTimer;
		int		_range;
		bool	_exploded;
		bool	_isCollide;
		std::vector<Explosion>		_explosionVector;
};