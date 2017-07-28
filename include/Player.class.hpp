#pragma once

#include <main.hpp>
#include <AEntity.class.hpp>
#include <Wall.class.hpp>

class Player : public AEntity
{
	public:

		Player();
		Player(Player const & src);
		~Player();

		void	movement(std::vector<Wall> & wall);
		bool	collision(std::vector<Wall> & wall);
		void	respawn();
		void	pickupPowerUps();
		void	evalScore();

		sf::Texture texture__; //TEMP MOFO, DELETE IT!
		sf::Sprite	sprite__; //ALSO TEMP!

	private:

		int			_lives;
		int			_score;
		int			_speed;
		int			_bombRange;
		int			_bombAmount;
		bool		_bombReady;
		bool		_isMoving;
		bool		_pickupPowerup;
		ePowerups	_typePowerup;
		eScore		_typeScore;

		//		Create Bomb type

		//		int		_keyPlaceBomb;
		sf::Keyboard::Key 	_keyMoveRight;
		sf::Keyboard::Key 	_keyMoveLeft;
		sf::Keyboard::Key 	_keyMoveUp;
		sf::Keyboard::Key 	_keyMoveDown;

};