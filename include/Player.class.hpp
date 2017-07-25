#pragma once

#include <main.hpp>
#include <AEntity.class.hpp>

class Player : public AEntity
{
	public:

		Player();
		Player(Player const & src);
		~Player();

		void	movement();
		void	collision();

	private:

		int		_lives;
		int		_score;
		bool	_canPlaceBombs;
		//		Create Bomb type
};