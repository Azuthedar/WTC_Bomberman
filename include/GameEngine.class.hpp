#pragma once
#include <Player.class.hpp>
#include <main.hpp>
#include <Wall.class.hpp>
#include <Enemy.class.hpp>

class Engine
{
	public:

		Engine();
		Engine(Engine const & src);
		~Engine();

		void		ticker();
		void		gameLogic();
		void		readMap(std::string fileName);
		void		buildMap();

		void		strSplit(std::string, char delim);


		Player &					getPlayer();
		std::vector<char> &			getMapValues();
		std::vector<Wall> &			getWallVector();
		std::vector<Enemy> &		getEnemyVector();

	private:

		std::vector<char>			_mapValues;
		std::vector<Wall>			_walls_vector;
		Player 						_player;
		std::vector<Enemy>			_enemyVector;

};