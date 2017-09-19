#pragma once

#include "Player.class.hpp"
#include "main.hpp"
#include "Wall.class.hpp"
#include "Enemy.class.hpp"
#include "Explosion.class.hpp"
#include "Powerup.class.hpp"
#include <Config.class.hpp>
#include "../../Sound_lib/include/SoundEngine.hpp"

class Engine
{
	public:

		Engine();
		// Engine(Engine const & src);
		~Engine();

		void		ticker( GLfloat &delta_time );
		void		transitionMap();
		void		gameLogic( GLFWwindow *window, GLfloat &delta_time );
		void		readFile(std::string fileName); // Point of this function is to read multiple maps.
		void		readMap();
		void		buildMap();
		void		shouldTransition();

		void		strSplit(std::string, char delim);
		void		chainReaction();

		void						setMapEnd(bool mapEnd);
		void						setGameState(eGamestate state);
		void						setIsTransitioning(bool transition);

		std::vector<char> &			getMapValues();
		std::vector<Wall> &			getWallVector();
		Player &					getPlayer();
		Gate &						getGate();
		std::vector<Enemy> &		getEnemyVector();
		std::vector<Explosion> &	getExplosionVector();
		std::vector<Explosion>		getAllExplosions();
		int &						getMapDuration();
		bool &						getMapEnd();
		std::vector<Powerup> &		getPowerupVector();
		Config &					getConfig();
		eGamestate &				getGameState();
		Sound &						getSound();

	private:

		std::vector<std::string>	_maps;
		std::vector<char>			_mapValues;
		std::vector<Wall>			_walls_vector;
		Player 						_player;
		Gate						_gate;
		std::vector<Enemy>			_enemyVector;
		int							_mapDuration;
		size_t						_mapLevel;
		int							_transitionTicker;
		bool						_mapEnd;
		bool						_isTransitioning;
		bool						_transition;
		Exceptions					_exceptions;
		std::vector<Powerup>		_powerupVector;
		Config						_config;

		eGamestate					_gameState;
		Sound						_sound;
		eSound						_soundEnum;
};
