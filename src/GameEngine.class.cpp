#include <GameEngine.class.hpp>

Engine::Engine()
{
	return ;
}

Engine::Engine(Engine const & src)
{
	*this = src;
}

Engine::~Engine()
{
	return ;
}

void Engine::gameLogic()
{
	this->_player.movement(this->_walls_vector);
	//Tick every bomb
	for (size_t i = 0; i < this->_player.getBombVector().size(); i++)
	{
		this->_player.getBombVector()[i].modifyCurrTimer(-1);
		if (this->_player.getBombVector()[i].getCurrTimer() <= 0)
		{
			this->_player.getBombVector()[i].explode();
			this->_player.getBombVector().erase(this->_player.getBombVector().begin() + i);
			this->_player.modifyBombs();
		}
	}
}

void		Engine::readMap(std::string fileName)
{
	char delim = ' ';
	std::ifstream file;
	std::string strValues;	//To read in the values read in from the file

	this->_mapValues.clear();
	file.open(fileName);

	if (!file)
		std::cout << "No file found" << std::endl;	//Throw exception for invalid file!
	if (!(fileName.substr(fileName.find_last_of(".") + 1) == "map"))
		std::cout << "Invalid file format." << std::endl;	//Throw exception for invalid file format!
	if (file.eof())
		std::cout << "Empty file." << std::endl;	//Throw exception for end of file found
	
	while (getline(file, strValues))
	{
		int i = 0;
		i++;
		this->strSplit(strValues, delim);
		if (i != MAP_Y)
			;//THROW EXCEPTION INVALID MAP SIZE
	}
	file.close();
}

void Engine::buildMap()
{
	int y = 0;
	char tmp;
	int playerFound = 0;
 	for (size_t i = 0; i < this->_mapValues.size(); i++)
	{
		tmp = this->_mapValues[i];
		if (i % MAP_Y == 0)
			y++;
		if (atoi(&tmp) == SOLID_BLOCK)
			this->_walls_vector.push_back(Wall((i % 16) * GRID_X, y * GRID_Y, SOLID_BLOCK));
		else if (atoi(&tmp) == DESTRUCTIBLE_BLOCK)
			this->_walls_vector.push_back(Wall((i % 16) * GRID_X, y * GRID_Y, DESTRUCTIBLE_BLOCK));
		else if (atoi(&tmp) == PLAYER)
		{
			i++;
			this->_player.setSpawnX((i % 16) * GRID_X);
			this->_player.setSpawnY((y * GRID_Y));
			this->_player.respawn();
		}
	}
	if (playerFound == 0 || playerFound > 1)
		std::cout << "Invalid amount of players" << std::endl;
	//Throw exception INVALID AMOUNT OF PLAYERS!
}

void	Engine::strSplit(std::string str, char delim)
{
	std::string newStr;
	int j = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != delim)
			;//throw EXCEPTION invalid map format
		else if (str[i] >= '0' && str[i] <= '9' && str[i + 1] >= '0' && str[i + 1] <= '9')
			;//Throw EXCEPTION invalid number format
		else if (str[i] >= '0' && str[i] <= '9')
		{
			newStr += str[i];
		}
	}
	if (j != MAP_X)
		;//Throw	EXCEPTION mapSize invalid
	static int i = 0;
 	for (size_t sz = 0; sz < newStr.length(); sz++)
	{
		i++;
		this->_mapValues.push_back(newStr[sz]);
	}
}

std::vector<char> &	Engine::getMapValues()	{return (this->_mapValues);}
Player & 					Engine::getPlayer() 	{return (this->_player);}
std::vector<Wall> &			Engine::getWallVector()	{return (this->_walls_vector);}