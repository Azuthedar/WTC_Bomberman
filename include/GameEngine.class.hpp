#pragma once
#include <Player.class.hpp>
#include <main.hpp>
#include <Wall.class.hpp>

class Engine
{
	public:

		Engine();
		Engine(Engine const & src);
		~Engine();

		void		readMap(std::string fileName);
		void		gameLogic();
		void		buildMap();

		void		strSplit(std::string, char delim);


		Player &					getPlayer();
		std::vector<char> &			getMapValues();
		std::vector<Wall> &			getWallVector();

	private:

		std::vector<char>		_mapValues;
		std::vector<Wall>				_walls_vector;
		Player 							_player;
};

