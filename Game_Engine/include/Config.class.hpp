#include <main.hpp>
#include <regex>
#include <fstream>
#include <Player.class.hpp>
#include <Exception.class.hpp>

class Config: public Exceptions
{
	public:
	
		Config();
		Config(std::string fileName);
		~Config();

		void	defaultInit(Player & player);
		void	reset(Player & player);
		void	readFile();
		bool	checkSyntax(); // True will be correct syntax
		void	parseFile(Player & player);
		void	updateFile(Player & player, int mapLevel);
		
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

	private:

		std::ifstream	_file;
		std::string		_fileName;
		std::vector<std::string> _fileBuffer;

		int		_mapLevel;

		int				_bombLevel;
		int				_rangeLevel;
		int				_lives;
		int				_speedLevel;

		int				_resX;
		int				_resY;
		int				_soundLevel;

		int				_KBmoveUp;
		int				_KBmoveLeft;
		int				_KBmoveRight;
		int				_KBmoveDown;
		int				_KBplaceBomb;
		int				_KBpause;
	};