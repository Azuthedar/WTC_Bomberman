#pragma once

#include <main.hpp>

class Engine
{
	public:

		Engine();
		Engine(Engine const & src);
		~Engine();

		void		readMap(std::string fileName);
		void		parseMap();

		void		setXSize(int xSize);
		void		setYSize(int ySize);

		std::vector<std::string>	getMapValues() const;
		int							getXSize() const;
		int							getYSize() const;

	private:

		std::vector<std::string>		_mapValues;
		int								_xSize;
		int								_ySize;
};

