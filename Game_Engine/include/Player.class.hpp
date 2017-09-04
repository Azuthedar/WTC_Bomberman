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

		int	&	getBombs();
		int &	getBombRange();
		int	&	getSpawnX();
		int	&	getSpawnY();
		int	&	getPlaceBombTimer();
		std::vector<Bomb> &		getBombVector();

	private:
		
		bool				change_dir;

		bool				collide_left;
		bool				collide_right;
		bool				collide_up;
		bool				collide_down;

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
		bool				_isMoving;
		bool				_pickupPowerup;
		bool				_hitOnce; // Used to check if the explosion has already hit the player.
		ePowerups			_typePowerup;
		eScore				_typeScore;
		std::vector<Bomb>	_bomb;
};
