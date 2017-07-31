#pragma once

#include <main.hpp>
#include <AEntity.class.hpp>

class Bomb : public AEntity
{
	public:

		Bomb();
		Bomb(int x, int y);
		Bomb(Bomb const & src);
		~Bomb();

		void	explode();

		void	setBombRange(int range);
		void	modifyCurrTimer(int currTimer);
		
		int	&	getCurrTimer(void);

		sf::Texture texture__; //TEMP MOFO, DELETE IT!
		sf::Sprite	sprite__; //ALSO TEMP!

	private:

		int _currTimer; // Explode timer will be on default added just in case for chain bombs exploding
		int _totalTimer;
		int _range;
};