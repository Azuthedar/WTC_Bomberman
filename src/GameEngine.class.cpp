#include <GameEngine.class.hpp>

Engine::Engine()
{
	this->_xSize = 0;
	this->_ySize = 0;
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

void		Engine::readMap(std::string fileName)
{
	char delim = ' '; // Delimiter to string split specified strings
	//bool errorFound = false;
	std::ifstream file;
	std::string strValues;	//To read in the values read in from the file

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
}

void	Engine::parseMap()
{

}

void	Engine::setXSize(int xSize) {this->_xSize = xSize;}
void	Engine::setYSize(int ySize) {this->_ySize = ySize;}

std::vector<std::string>	Engine::getMapValues() const {return (this->_mapValues);}
int							Engine::getXSize() const {return (this->_xSize);}
int							Engine::getYSize() const {return (this->_ySize);}