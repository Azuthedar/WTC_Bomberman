#pragma once

#include <main.hpp>
#include <AEntity.class.hpp>
#include <Wall.class.hpp>
#include <Bomb.class.hpp>

class Player : public AEntity
{
	public:

		Player();
		Player(int x, int y);
		Player(Player const & src);
		~Player();


		void	init();
		void	movement(std::vector<Wall> & wall);
		bool	collision(std::vector<Wall> & wall);
		bool	isBombThere(int x, int y);
		void	respawn();
		void	pickupPowerUps();
		void	evalScore();

		void	modifyBombs();

		int		getBombs();
		std::vector<Bomb> &		getBombVector();

		sf::Texture texture__; //TEMP MOFO, DELETE IT!
		sf::Sprite	sprite__; //ALSO TEMP!

	private:

		int					_lives;
		int					_score;
		int					_speed;
		int					_bombRange;
		int					_bombs;
		bool				_isMoving;
		bool				_pickupPowerup;
		ePowerups			_typePowerup;
		eScore				_typeScore;
		std::vector<Bomb>	_bomb;

		sf::Keyboard::Key	_keyPlaceBomb;
		sf::Keyboard::Key 	_keyMoveRight;
		sf::Keyboard::Key 	_keyMoveLeft;
		sf::Keyboard::Key 	_keyMoveUp;
		sf::Keyboard::Key 	_keyMoveDown;

};