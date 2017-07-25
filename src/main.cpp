#include <main.hpp>
#include <AEntity.class.hpp>
#include <Player.class.hpp>
#include <GameEngine.class.hpp>

int main(int argc, char **argv)
{
	Engine newEngine;
	if (argc == 1)
	{
		std::cout << "Invalid execution, please input a valid file. (Valid files end in .map)" << std::endl;
		return (0);
	}
	newEngine.readMap(argv[1]);
	return (0);
}