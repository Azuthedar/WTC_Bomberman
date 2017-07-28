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
	this->_p2.setSpeed(6);
	this->_p2.movement(this->_walls_vector);
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
	
	while (getline(file, strValues, delim))
	{
		this->_mapValues.push_back(strValues);
	}
	file.close();
}

void Engine::buildMap()
{
	int y = 0;

 	for (size_t i = 0; i < this->_mapValues.size(); i++)
	{
		if (i % MAP_Y == 0)
			y++;
		if (stoi(this->_mapValues[i]) == SOLID_BLOCK)
			this->_walls_vector.push_back(Wall((i % 16) * GRID_X, y * GRID_Y, SOLID_BLOCK));
		if (stoi(this->_mapValues[i]) == DESTRUCTIBLE_BLOCK)
			this->_walls_vector.push_back(Wall((i % 16) * GRID_X, y * GRID_Y, DESTRUCTIBLE_BLOCK));
	}
}

std::vector<std::string> &	Engine::getMapValues()	{return (this->_mapValues);}
Player & 					Engine::getPlayer() 	{return (this->_player);}
std::vector<Wall> &			Engine::getWallVector()	{return (this->_walls_vector);}