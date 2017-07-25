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
/*
		int	placeBomb;
		int 	_moveRight;
		int 	_moveLeft;
		int 	_moveUp;
		int 	_moveDown;
*/


};