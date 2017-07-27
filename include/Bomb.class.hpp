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

		void	setRange(int range);
		void	setAmount(int amount);

	private:

		int _bombExplodeTimer; // Explode timer will be on default added just in case for chain bombs exploding
		int _range;
		int _amount;
};