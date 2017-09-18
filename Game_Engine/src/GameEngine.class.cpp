#include "../include/GameEngine.class.hpp"

Engine::Engine()
{
	this->_mapDuration = MAP_DURATION_TIME;
	this->_transitionTicker = MAP_TRANSITION_TIME;
	this->_mapEnd = false;
	this->_isTransitioning = false;
	this->_config.defaultInit(this->_player, this->_sound);
	this->_gameState = MENU;
	this->_mapLevel = this->_config.getMapLevel();
	this->readFile("maps");
	this->readMap();
	//this->buildMap();
	this->_sound.playMusic();
	return ;
}

/* Engine::Engine(Engine const & src)
{
	*this = src;
} */

Engine::~Engine()
{
	return ;
}

void Engine::ticker( GLfloat &delta_time  )
{
	//	TICKER for bombs
	for (size_t i = 0; i < this->_player.getBombVector().size(); i++)
	{
		this->_player.getBombVector()[i].modifyCurrTimer(-1);
		this->_player.getBombVector()[i].destroyExplosion(delta_time);
		if (this->_player.getBombVector()[i].getCurrTimer() <= 0 && this->_player.getBombVector()[i].getExploded() == false)
		{
			this->_player.getBombVector()[i].explode(this->_player.getBombRange(), this->_walls_vector, this->_powerupVector, this->_gate);
			if (this->_soundEnum != SND_DEATH && this->_soundEnum != SND_LVLCOMPLETE && this->_soundEnum != SND_GAMEOVER
				&& this->_soundEnum != SND_GATEUNLOCKED && this->_soundEnum != SND_GATEFOUND)
				this->_soundEnum = SND_EXPLOSION;
			this->_player.modifyBombs();
		}
		if (this->_player.getBombVector()[i].getCurrTimer() <= -1)
		{
			this->_player.getBombVector().erase(this->_player.getBombVector().begin() + i);
		}

	}
	this->_player.modifyPlaceBombTimer();

	//	TICKER for enemy movement
	for (size_t i = 0; i < this->_enemyVector.size(); i++)
	{
		if (this->_enemyVector[i].getIsDead())
			this->_enemyVector.erase(this->_enemyVector.begin() + i);
		this->_enemyVector[i].movement(this->_walls_vector, this->_enemyVector, this->_player.getBombVector(), delta_time );
		this->_enemyVector[i].modifyEnemyMvTicker();
	}
	this->_mapDuration--;
}

void Engine::transitionMap()
{
	this->_transitionTicker--;
	if (this->_transitionTicker <= 0 && this->_isTransitioning)
	{
		/*
		*	A temporary solution to the fact that there aren't infinite maps.
		*	After you finish the game transition to CREDITS / MAIN_MENU?
		*/
		if (this->_mapLevel == this->_maps.size())
			this->_mapLevel = 0;
		this->_mapEnd = true;
		this->_gate.setExists(false);
		this->_gate.setIsLocked(true);
		this->_mapValues.clear();
		this->_enemyVector.clear();
		this->_player.respawn();
		this->_walls_vector.clear();
		this->_config.updateFile(this->_player, this->_mapLevel, this->_sound);
		this->readMap();
		this->buildMap();
		this->_player.getBombVector().clear();
		this->_powerupVector.clear();
		this->_mapDuration = MAP_DURATION_TIME;
		this->_transitionTicker = MAP_TRANSITION_TIME;
		this->_isTransitioning = false;
	}
}

void Engine::gameLogic( GLFWwindow *window, GLfloat &delta_time )
{
	if (this->_gameState == MENU)
	{
		if (glfwGetKey(window, GLFW_KEY_ENTER))
		{
			this->_gameState = GAME;
			this->_isTransitioning = true;
			this->transitionMap();
		}
	}
	if (this->_gameState == GAME)
	{
		if (this->_mapDuration <= 0)
		{
			static float ticker = 3.0f;
			this->_soundEnum = SND_GAMEOVER;
			ticker -= delta_time;
			if (ticker <= 0)
			{
				ticker = 3.0f;
				this->_gameState = MENU;
			}
			std::cout << "Time's Up!" << std::endl;
		}
		else if (!this->_isTransitioning)
		{
			static bool gateFound = false;
			if (!gateFound && this->_gate.getExists())
			{
				gateFound = true;
				this->_soundEnum = SND_GATEFOUND;
			}
			if (this->_player.getLives() <= 0)
			{
				this->_config.reset(this->_player, this->_sound);
				this->_mapLevel = 0;
				this->_gameState = MENU;
				//Make player transition to main menu
			}

			if (this->_gate.getIsLocked() == true && (this->_enemyVector.size() == 0 || glfwGetKey(window, GLFW_KEY_L)))
			{
				if (this->_gate.getExists())
					this->_soundEnum = SND_GATEUNLOCKED;
				this->_gate.setIsLocked(false);
			}
			this->_player.input( window );
			this->_player.movement(this->_walls_vector, this->_enemyVector, this->_powerupVector, delta_time);
			this->chainReaction();
			this->ticker( delta_time );
			this->shouldTransition();
		}
		else
			this->transitionMap();
	}
	this->_sound.playSound(this->_soundEnum, this->_player.getSoundEnum(), this->_gameState);

}

void		Engine::readFile(std::string fileName)
{
	struct stat		st;
	std::ifstream	file;
	std::string		newString;

	file.open(fileName);
	lstat(fileName.c_str(), &st);
	if (!file || !S_ISREG(st.st_mode))
		this->_exceptions.throwNoFile();
	else if (fileName != "maps")
	{
		std::cout << "Invalid file name. Required name is \'maps\'" << std::endl;
		this->_exceptions.throwInvalidFile();
	}
	while (getline(file, newString))
	{
		this->_maps.push_back(newString);
	}
}

void		Engine::readMap()
{
	struct stat st;
	char delim = ' ';
	std::ifstream file;
	std::string strValues;	//To read in the values read in from the file
	int i = 0;

	//this->_mapValues.clear();
	file.open(this->_maps[this->_mapLevel]);
	lstat(this->_maps[this->_mapLevel].c_str(), &st); //Checks the name, and passes it to the struct
	if (!file || !S_ISREG(st.st_mode)) // Check that the file exists and that it's not a directory
		this->_exceptions.throwNoFile();	//Throw exception for invalid file!
	else if (!(this->_maps[this->_mapLevel].substr(this->_maps[this->_mapLevel].find_last_of(".") + 1) == "map"))
		this->_exceptions.throwInvalidFile();	//Throw exception for invalid file!
	else if (file.eof())
		this->_exceptions.throwEmptyFile();	//Throw exception for end of file found

	while (getline(file, strValues))
	{
		i++;
		this->strSplit(strValues, delim);
	}
	if (i != MAP_Y)
			this->_exceptions.throwMapSizeInvalid();
	file.close();
	this->_mapLevel++;
}

void Engine::buildMap()
{
	int y = 0;
	char tmp;
	int playerFound = 0;
	int gateFound = 0;
 	for (size_t i = 0; i < this->_mapValues.size(); i++)
	{
		tmp = this->_mapValues[i];
		if (i % MAP_Y == 0)
			y++;
		if (atoi(&tmp) == SOLID_BLOCK)
			this->_walls_vector.push_back(Wall((i % MAP_X), y, SOLID_BLOCK));
		else if (atoi(&tmp) == DESTRUCTIBLE_BLOCK)
			this->_walls_vector.push_back(Wall((i % MAP_X), y, DESTRUCTIBLE_BLOCK));
		else if (atoi(&tmp) == ENEMY_BLOCK)
			this->_enemyVector.push_back(Enemy((i % MAP_X), y));
		else if (atoi(&tmp) == GATE)
		{
			this->_walls_vector.push_back(Wall((i % MAP_X), y, GATE));
			gateFound++;
		}
		else if (atoi(&tmp) == PLAYER)
		{
			playerFound++;
			this->_player.setSpawnX((i % MAP_X));
			this->_player.setSpawnY(( y ));
			this->_player.respawn();
		}
	}
	if (playerFound == 0 || playerFound > 1)
		this->_exceptions.throwInvalidPlayer();	//Throw exception INVALID AMOUNT OF PLAYERS!
	if (gateFound == 0 || gateFound > 1)
		this->_exceptions.throwInvalidGates();	//Throw exception INVALID AMOUNT OF GATES!
}

void	Engine::strSplit(std::string str, char delim)
{
	std::string newStr;
	int j = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != delim)
			this->_exceptions.throwMapInvalid();	//Throw EXCEPTION invalid map format
		else if (str[i] >= '0' && str[i] <= '9' && str[i + 1] >= '0' && str[i + 1] <= '9')
			this->_exceptions.throwMapInvalid();	//Throw EXCEPTION invalid number format
		else if (str[i] >= '0' && str[i] <= '9')
		{
			newStr += str[i];
			j++;
		}
	}
	if (j != MAP_X)
		this->_exceptions.throwMapSizeInvalid();	//Throw	EXCEPTION mapSize invalid
	static int i = 0;
 	for (size_t sz = 0; sz < newStr.length(); sz++)
	{
		i++;
		this->_mapValues.push_back(newStr[sz]);
	}
}

void		Engine::shouldTransition()
{
	if (this->_player.getXPos() == this->_gate.getXPos() && this->_player.getYPos() == this->_gate.getYPos() && !this->_gate.getIsLocked())
	{
		this->_soundEnum = SND_LVLCOMPLETE;
		this->_isTransitioning = true;
	}
}

std::vector<Explosion>		Engine::getAllExplosions()
{
	std::vector <Explosion> allExplosions;
	for (size_t b = 0; b < this->_player.getBombVector().size(); b++)
	{
		for (size_t e = 0; e < this->_player.getBombVector()[b].getExplosionVector().size(); e++)
		{
			allExplosions.push_back(this->_player.getBombVector()[b].getExplosionVector()[e]);
		}
	}
	return (allExplosions);
}

void	Engine::chainReaction()
{
	std::vector<Explosion> allExplosions;
	allExplosions.clear();
	allExplosions = this->getAllExplosions();
	for (size_t b = 0; b < this->_player.getBombVector().size(); b++)
	{
		for (size_t i = 0; i < allExplosions.size(); i++)
		{
			if (this->_player.getBombVector()[b].getXPos() == allExplosions[i].getXPos() && this->_player.getBombVector()[b].getYPos() == allExplosions[i].getYPos() && this->_player.getBombVector()[b].getExploded() == false)
			{
				this->_player.getBombVector()[b].explode(this->_player.getBombRange(), this->_walls_vector, this->_powerupVector, this->_gate);
				this->_player.modifyBombs();
				break ;
			}
		}
	}
}

void						Engine::setMapEnd(bool mapEnd)	{this->_mapEnd = mapEnd;}

std::vector<char> &			Engine::getMapValues()			{return (this->_mapValues);}
Player & 					Engine::getPlayer() 			{return (this->_player);}
Gate &						Engine::getGate()				{return (this->_gate);}
std::vector<Wall> &			Engine::getWallVector()			{return (this->_walls_vector);}
std::vector<Enemy> &		Engine::getEnemyVector()		{return (this->_enemyVector);}
int &						Engine::getMapDuration()		{return ((this->_mapDuration > 0) ? this->_mapDuration : this->_mapDuration = 0);}
bool &						Engine::getMapEnd()				{return (this->_mapEnd);}
std::vector<Powerup> &		Engine::getPowerupVector()		{return (this->_powerupVector);}
Config &					Engine::getConfig()				{return (this->_config);}
