#pragma once

#include "main.hpp"
#include "AEntity.class.hpp"
#include "Wall.class.hpp"
#include "Bomb.class.hpp"
#include "Enemy.class.hpp"
#include "Powerup.class.hpp"

class Player : public AEntity
{
	public:

		Player();
		Player(int x, int y);
		Player(Player const & src);
		~Player();


		void	init();
		void	input( GLFWwindow *window );
		void	movement(std::vector<Wall> & wall, std::vector<Enemy> & enemy, std::vector<Powerup> & powerupVector, GLfloat &deltaTime );
		bool	collision(std::vector<Wall> & wall, std::vector<Enemy> & enemy, std::vector<Powerup> & powerupVector);
		void	checkBombPlacement(int & place_x, int & place_y);
		bool	isBombThere(int x, int y);
		void	respawn();
		void	pickupPowerUps(ePowerups type);
		void	evalScore();
		void 	SnapMovement();

		void	modifyBombs();
		void	modifyPlaceBombTimer();

		void	setSpawnX(int spawnX);
		void	setSpawnY(int spawnY);
		void	setSpeedLevel(int speedLevel);
		void	setRangeLevel(int rangeLevel);
		void	setBombLevel(int bombLevel);
		void	setLives(int lives);
		void	setKBMoveUp(int KBmoveUp);
		void	setKBMoveLeft(int KBmoveLeft);
		void	setKBMoveRight(int KBmoveRight);
		void	setKBMoveDown(int KBmoveDown);
		void	setKBPlaceBomb(int KBplaceBomb);
		void	setKBPause(int KBpause);

		int	&	getBombs();
		int &	getBombRange();
		int	&	getSpawnX();
		int	&	getSpawnY();
		int	&	getPlaceBombTimer();
		int &	getSpeedLevel();
		int &	getRangeLevel();
		int &	getBombLevel();
		int & 	getLives();
		int &	getKBMoveUp();
		int &	getKBMoveLeft();
		int &	getKBMoveRight();
		int &	getKBMoveDown();
		int &	getKBPlaceBomb();
		int &	getKBPause();
		std::vector<Bomb> &		getBombVector();

	private:

		int					_goal_x;
		int					_goal_y;

		int					_lives;
		int					_totalLives;
		int					_score;

		float				_totalSpeed;
		int					_bombRange;
		int					_bombs;
		int					_spawnX;
		int					_spawnY;
		int					_placeBombTimer;
		float				_speed;

		int					_speedLevel;
		int					_rangeLevel;
		int					_bombLevel;
		
		bool				_isMoving;
		bool				_pickupPowerup;
		bool				_hitOnce; // Used to check if the explosion has already hit the player.
		ePowerups			_typePowerup;
		eScore				_typeScore;
		std::vector<Bomb>	_bomb;

		int					_KBmoveUp;
		int					_KBmoveLeft;
		int					_KBmoveRight;
		int					_KBmoveDown;
		int					_KBplaceBomb;
		int					_KBpause;
};
