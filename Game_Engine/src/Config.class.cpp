#include <Config.class.hpp>

Config::Config()
{
	this->_fileName = "config.init";
	return ;
}

Config::~Config()
{
	this->_file.close();
	return ;
}

void    Config::defaultInit( Player & player ) //, Sound & sound)
{
	this->_file.open(this->_fileName);
	if (!this->_file)
	{
		std::ofstream configFile;
		configFile.open(this->_fileName);
		// MAP DATA
		configFile << "[MAP]" << std::endl;
		configFile << "\tMAPLEVEL: 0" << std::endl;

		// PLAYER LEVEL DATA
		configFile << "[LEVELS]" << std::endl;
		configFile << "\tBOMBLEVEL: 1" << std::endl;
		configFile << "\tRANGELEVEL: 1" << std::endl;
		configFile << "\tSPEEDLEVEL: 1" << std::endl;
		configFile << "\tLIVES: 3" << std::endl;

		// OPTIONS DATA
		configFile << "[OPTIONS]" << std::endl;
		configFile << "\tRESOLUTION: 1920 1080" << std::endl;
		configFile << "\tSFX: 100" << std::endl;
		configFile << "\tMUSIC: 100" << std::endl;

		// KEYBINDINGS DATA
		configFile << "[KEYBINDINGS]" << std::endl;
		configFile << "\tUP: 87" << std::endl;
		configFile << "\tLEFT: 65" << std::endl;
		configFile << "\tRIGHT: 68" << std::endl;
		configFile << "\tDOWN: 83" << std::endl;
		configFile << "\tPLACEBOMB: 32" << std::endl;
		configFile << "\tPAUSE: 52" << std::endl;

		configFile.close();
	}
	this->_file.close();
	this->parseFile(player); //, sound);
}

void	Config::reset( Player & player )//, Sound & sound)
{
	if (std::remove(this->_fileName.c_str()) == 0)
		defaultInit(player); //, sound);
	else
		this->throwFileFailedDelete();
	return ;
}

void    Config::readFile()
{
	std::string line;
	while (getline(this->_file, line))
		this->_fileBuffer.push_back(line);
}

bool	Config::checkSyntax()
{
	/*Maps*/
	std::regex rgx_map("^\\[MAP\\]$");
	std::regex rgx_map1("^\tMAPLEVEL: [0-9]+");

	/*Player level data*/
	std::regex rgx_levels("^\\[LEVELS\\]$");
	std::regex rgx_levels1("^\tBOMBLEVEL: ([1-9]|10)$");
	std::regex rgx_levels2("^\tRANGELEVEL: ([1-9]|10)$");
	std::regex rgx_levels3("^\tSPEEDLEVEL: ([1-9]|10)$");
	std::regex rgx_levels4("^\tLIVES: ([0-9]|10)$");

	/*Option data*/
	std::regex rgx_options("^\\[OPTIONS\\]$");
	std::regex rgx_options1("^\tRESOLUTION: [0-9]{3,4} [0-9]{3,4}$");
	std::regex rgx_options2("^\tSFX: ([0-9]{1,2}|100)$");
	std::regex rgx_options3("^\tMUSIC: ([0-9]{1,2}|100)$");

	/*Keybinding data*/
	std::regex rgx_kb("^\\[KEYBINDINGS\\]$");
	std::regex rgx_kbUp("^\tUP: [0-9]{1,3}$");
	std::regex rgx_kbLeft("^\tLEFT: [0-9]{1,3}$");
	std::regex rgx_kbRight("^\tRIGHT: [0-9]{1,3}$");
	std::regex rgx_kbDown("^\tDOWN: [0-9]{1,3}$");
	std::regex rgx_kbBomb("^\tPLACEBOMB: [0-9]{1,3}$");
	std::regex rgx_kbPause("^\tPAUSE: [0-9]{1,3}$");

	if (std::regex_match(this->_fileBuffer[0], rgx_map) && std::regex_match(this->_fileBuffer[1], rgx_map1)
		&& std::regex_match(this->_fileBuffer[2], rgx_levels) && std::regex_match(this->_fileBuffer[3], rgx_levels1)
		&& std::regex_match(this->_fileBuffer[4], rgx_levels2) && std::regex_match(this->_fileBuffer[5], rgx_levels3)
		&& std::regex_match(this->_fileBuffer[6], rgx_levels4)
		&& std::regex_match(this->_fileBuffer[7], rgx_options) && std::regex_match(this->_fileBuffer[8], rgx_options1)
		&& std::regex_match(this->_fileBuffer[9], rgx_options2) && std::regex_match(this->_fileBuffer[10], rgx_options3)
		&& std::regex_match(this->_fileBuffer[11], rgx_kb) && std::regex_match(this->_fileBuffer[12], rgx_kbUp)
		&& std::regex_match(this->_fileBuffer[13], rgx_kbLeft) && std::regex_match(this->_fileBuffer[14], rgx_kbRight)
		&& std::regex_match(this->_fileBuffer[15], rgx_kbDown) && std::regex_match(this->_fileBuffer[16], rgx_kbBomb)
		&& std::regex_match(this->_fileBuffer[17], rgx_kbPause))
		return (true);

	return (false);
}

void    Config::parseFile(Player & player) //, Sound & sound)
{
	this->_file.open(this->_fileName);
	this->readFile();
	if (this->checkSyntax())
	{
		//Set all the current data
		// MAPNAME
		this->_mapLevel = std::stoi(this->_fileBuffer[CNF_MAP].substr(this->_fileBuffer[CNF_MAP].find_first_of(' ', 4), this->_fileBuffer[CNF_MAP].length() - 1));

		// LEVEL DATA
		this->_bombLevel = std::stoi(this->_fileBuffer[CNF_BOMBLVL].substr(this->_fileBuffer[CNF_BOMBLVL].find_first_of(' ', 4) + 1, this->_fileBuffer[CNF_BOMBLVL].length() - 1));
		this->_rangeLevel = std::stoi(this->_fileBuffer[CNF_RANGELVL].substr(this->_fileBuffer[CNF_RANGELVL].find_first_of(' ', 4) + 1, this->_fileBuffer[CNF_RANGELVL].length() - 1));
		this->_speedLevel = std::stoi(this->_fileBuffer[CNF_SPEEDLVL].substr(this->_fileBuffer[CNF_SPEEDLVL].find_first_of(' ', 4) + 1, this->_fileBuffer[CNF_SPEEDLVL].length() - 1));
		this->_lives = std::stoi(this->_fileBuffer[CNF_LIVES].substr(this->_fileBuffer[CNF_LIVES].find_first_of(' ', 4) + 1, this->_fileBuffer[CNF_LIVES].length() - 1));

		// OPTIONS DATA
		this->_resX = std::stoi(this->_fileBuffer[CNF_RESOLUTION].substr(this->_fileBuffer[CNF_RESOLUTION].find_first_of(' ', 4) + 1, this->_fileBuffer[CNF_RESOLUTION].find_last_of(' ') - 1));
		this->_resY = std::stoi(this->_fileBuffer[CNF_RESOLUTION].substr(this->_fileBuffer[CNF_RESOLUTION].find_last_of(' ') + 1, this->_fileBuffer[CNF_RESOLUTION].length() - 1));
		this->_SFXVolume = std::stoi(this->_fileBuffer[CNF_SFXVOL].substr(this->_fileBuffer[CNF_SFXVOL].find_first_of(' ', 4) + 1, this->_fileBuffer[CNF_SFXVOL].length() - 1));
		this->_musicVolume = std::stoi(this->_fileBuffer[CNF_MUSCVOL].substr(this->_fileBuffer[CNF_MUSCVOL].find_first_of(' ', 4) + 1, this->_fileBuffer[CNF_MUSCVOL].length() - 1));

		// KEYBINDINGS DATA
		this->_KBmoveUp = std::stoi(this->_fileBuffer[CNF_KBUP].substr(this->_fileBuffer[CNF_KBUP].find_first_of(' ', 4) + 1, this->_fileBuffer[CNF_KBUP].length() - 1));
		this->_KBmoveLeft = std::stoi(this->_fileBuffer[CNF_KBLEFT].substr(this->_fileBuffer[CNF_KBLEFT].find_first_of(' ', 4) + 1, this->_fileBuffer[CNF_KBLEFT].length() - 1));
		this->_KBmoveRight = std::stoi(this->_fileBuffer[CNF_KBRIGHT].substr(this->_fileBuffer[CNF_KBRIGHT].find_first_of(' ', 4) + 1, this->_fileBuffer[CNF_KBRIGHT].length() - 1));
		this->_KBmoveDown = std::stoi(this->_fileBuffer[CNF_KBDOWN].substr(this->_fileBuffer[CNF_KBDOWN].find_first_of(' ', 4) + 1, this->_fileBuffer[CNF_KBDOWN].length() - 1));
		this->_KBplaceBomb = std::stoi(this->_fileBuffer[CNF_KBPLACE].substr(this->_fileBuffer[CNF_KBPLACE].find_first_of(' ', 4) + 1, this->_fileBuffer[CNF_KBPLACE].length() - 1));
		this->_KBpause = std::stoi(this->_fileBuffer[CNF_KBPAUSE].substr(this->_fileBuffer[CNF_KBPAUSE].find_first_of(' ', 4) + 1, this->_fileBuffer[CNF_KBPAUSE].length() - 1));


		//sound.setSFXVolume(this->_SFXVolume);
		//sound.setMusicVolume(this->_musicVolume);

		player.setBombLevel(this->_bombLevel);
		player.setRangeLevel(this->_rangeLevel);
		player.setSpeedLevel(this->_speedLevel);
		player.setLives(this->_lives);

		player.setSpeed(6 * pow(1.03, player.getSpeedLevel()));
		player.setBombRange(player.getRangeLevel());
		player.setBombs(player.getBombLevel());

		player.setKBMoveUp(this->_KBmoveUp);
		player.setKBMoveLeft(this->_KBmoveLeft);
		player.setKBMoveRight(this->_KBmoveRight);
		player.setKBMoveDown(this->_KBmoveDown);
		player.setKBPlaceBomb(this->_KBplaceBomb);
		player.setKBPause(this->_KBpause);
	}
	else
	{
		this->throwInvalidSyntax();
	}
	this->_file.close();
}

void    Config::updateFile(Player & player, int mapLevel) //, Sound & sound)
{
	if (std::remove(this->_fileName.c_str()) == 0)
	{
		//Mix_HaltChannel(0);
		std::ofstream configFile;
		configFile.open(this->_fileName);

		this->_mapLevel = mapLevel;

		this->_bombLevel = player.getBombLevel();
		this->_rangeLevel = player.getRangeLevel();
		this->_speedLevel = player.getSpeedLevel();
		this->_lives = player.getLives();

		/* Temp this needs to be changed!!! */
		this->_resX = 1920;
		this->_resY = 1080;

		//this->_SFXVolume = sound.getSFXVolume();
		//this->_musicVolume = sound.getMusicVolume();

		this->_KBmoveUp = player.getKBMoveUp();
		this->_KBmoveLeft = player.getKBMoveLeft();
		this->_KBmoveRight = player.getKBMoveRight();
		this->_KBmoveDown = player.getKBMoveDown();
		this->_KBplaceBomb = player.getKBPlaceBomb();
		this->_KBpause = player.getKBPause();

		configFile << "[MAP]" << std::endl;
		configFile << "\tMAPLEVEL: " << std::to_string(this->_mapLevel) << std::endl;

		// PLAYER LEVEL DATA
		configFile << "[LEVELS]" << std::endl;
		configFile << "\tBOMBLEVEL: " << std::to_string(this->_bombLevel) << std::endl;
		configFile << "\tRANGELEVEL: " << std::to_string(this->_rangeLevel) << std::endl;
		configFile << "\tSPEEDLEVEL: " << std::to_string(this->_speedLevel) << std::endl;
		configFile << "\tLIVES: " << std::to_string(this->_lives) << std::endl;

		// OPTIONS DATA
		configFile << "[OPTIONS]" << std::endl;
		configFile << "\tRESOLUTION: " << std::to_string(this->_resX) << " " << std::to_string(this->_resY) << std::endl;
		configFile << "\tSFX: " << std::to_string(this->_SFXVolume) << std::endl;
		configFile << "\tMUSIC: " << std::to_string(this->_musicVolume) << std::endl;

		// KEYBINDINGS DATA
		configFile << "[KEYBINDINGS]" << std::endl;
		configFile << "\tUP: " << std::to_string(this->_KBmoveUp) << std::endl;
		configFile << "\tLEFT: " << std::to_string(this->_KBmoveLeft) << std::endl;
		configFile << "\tRIGHT: " << std::to_string(this->_KBmoveRight) << std::endl;
		configFile << "\tDOWN: " << std::to_string(this->_KBmoveDown) << std::endl;
		configFile << "\tPLACEBOMB: " << std::to_string(this->_KBplaceBomb) << std::endl;
		configFile << "\tPAUSE: " << std::to_string(this->_KBpause) << std::endl;

		//Mix_VolumeChunk( sound.getWaveVector()[SND_DEFAULT], this->_musicVolume * 0.6f);
		//if (Mix_PlayChannel(0, sound.getWaveVector()[SND_DEFAULT], -1) == -1)
		//	std::cerr << "TRANSITION: Failed to play sound: DEFAULT" << std::endl;

		configFile.close();
	}
	else
		this->throwFileFailedDelete();
}

void	Config::setMapLevel(int mapLevel) 			{this->_mapLevel = mapLevel;}
void    Config::setBombLevel(int bombLevel)     	{this->_bombLevel = bombLevel;}
void    Config::setRangeLevel(int rangeLevel)   	{this->_rangeLevel = rangeLevel;}
void    Config::setLives(int lives)             	{this->_lives = lives;}
void    Config::setSpeedLevel(int speedLevel)   	{this->_speedLevel = speedLevel;}
void    Config::setKBMoveUp(int KBmoveUp)           {this->_KBmoveUp = KBmoveUp;}
void    Config::setKBMoveLeft(int KBmoveLeft)       {this->_KBmoveLeft = KBmoveLeft;}
void    Config::setKBMoveRight(int KBmoveRight)     {this->_KBmoveRight = KBmoveRight;}
void    Config::setKBMoveDown(int KBmoveDown)     	{this->_KBmoveDown = KBmoveDown;}
void    Config::setKBPlaceBomb(int KBplaceBomb)		{this->_KBplaceBomb = KBplaceBomb;}
void	Config::setKBPause(int KBpause)				{this->_KBpause = KBpause;}
//void	Config::setSFXVolume(int sfxVol)			{this->_SFXVolume = sfxVol;}
//void	Config::setMusicVolume(int muscVol)			{this->_musicVolume = muscVol;}



int &	Config::getMapLevel() 			{return (this->_mapLevel);}
int &	Config::getBombLevel()          {return (this->_bombLevel);}
int &	Config::getRangeLevel()         {return (this->_rangeLevel);}
int &	Config::getLives()              {return (this->_lives);}
int &	Config::getSpeedLevel()         {return (this->_speedLevel);}
int &	Config::getKBMoveUp()           {return (this->_KBmoveUp);}
int &	Config::getKBMoveLeft()         {return (this->_KBmoveLeft);}
int &	Config::getKBMoveRight()        {return (this->_KBmoveRight);}
int &	Config::getKBMoveDown()         {return (this->_KBmoveDown);}
int &	Config::getKBPlaceBomb()        {return (this->_KBplaceBomb);}
int &	Config::getKBPause()			{return (this->_KBpause);}
//int &	Config::getSFXVolume()			{return (this->_SFXVolume);}
//int &	Config::getMusicVolume()		{return (this->_musicVolume);}
