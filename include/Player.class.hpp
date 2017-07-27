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

		sf::Texture texture__; //TEMP MOFO, DELETE IT!
		sf::Sprite	sprite__; //ALSO TEMP!

	private:

		int		_lives;
		int		_score;
		int		_speed;
		bool	_bombReady;
		bool	_isMoving;

		//		Create Bomb type

		//		int		_keyPlaceBomb;
		sf::Keyboard::Key 	_keyMoveRight;
		sf::Keyboard::Key 	_keyMoveLeft;
		sf::Keyboard::Key 	_keyMoveUp;
		sf::Keyboard::Key 	_keyMoveDown;

};