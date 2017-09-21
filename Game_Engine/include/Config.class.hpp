#pragma once

#include <main.hpp>
#include <regex>
#include <fstream>
#include <Player.class.hpp>
#include <Exception.class.hpp>
#include "../../Sound_lib/include/SoundEngine.hpp"

class Config: public Exceptions
{
	public:

		Config();
		Config(std::string fileName);


	~Config();

		void	defaultInit(Player & player, Sound & sound);
		void	readFile();
		bool	checkSyntax(); // True will be correct syntax
		void	parseFile(Player & player, Sound & sound);
		void	updateFile(Player & player, size_t & mapLevel, Sound & sound);

		void	setMapLevel(int mapLevel);
		void	setBombLevel(int bomblevel);
		void	setRangeLevel(int rangeLevel);
		void	setLives(int lives);
		void	setSpeedLevel(int speedLevel);
		void	setKBMoveUp(int KBmoveUp);
		void	setKBMoveLeft(int KBmoveLeft);
		void	setKBMoveRight(int KBmoveRight);
		void	setKBMoveDown(int KBmoveDown);
		void	setKBPlaceBomb(int placeBomb);
		void	setKBPause(int KBpause);
		void	setSFXVolume(int sfxVol);
		void	setMusicVolume(int muscVol);
		void	setConfigUpdated(bool updated);

		int &	getMapLevel();
		int &	getBombLevel();
		int &	getRangeLevel();
		int &	getLives();
		int &	getSpeedLevel();
		int &	getKBMoveUp();
		int &	getKBMoveLeft();
		int &	getKBMoveRight();
		int &	getKBMoveDown();
		int &	getKBPlaceBomb();
		int &	getKBPause();
		int &	getSFXVolume();
		int &	getMusicVolume();
		bool & getConfigUpdated();

	private:

		std::ifstream	_file;
		std::string		_fileName;
		std::vector<std::string> _fileBuffer;

		int				_mapLevel;

		int				_bombLevel;
		int				_rangeLevel;
		int				_lives;
		int				_speedLevel;

		int				_resX;
		int				_resY;
		int				_SFXVolume;
		int				_musicVolume;

		int				_KBmoveUp;
		int				_KBmoveLeft;
		int				_KBmoveRight;
		int				_KBmoveDown;
		int				_KBplaceBomb;
		int				_KBpause;

		bool			_configUpdated;
		bool			_shouldUpdate;
		bool			_shouldReset;
	};
