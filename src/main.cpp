#include <main.hpp>
#include <AEntity.class.hpp>
#include <Player.class.hpp>
#include <GameEngine.class.hpp>
#include <Wall.class.hpp>

void	__temp_render(Engine &engine, sf::RenderWindow &window);
void	__load_assets(Engine &engine);

int main(int argc, char **argv)
{

	if (argc == 1)
	{
		return (0);
	}
	Engine engine;

	engine.readMap(argv[1]);

	//Load Map Into Respective Vectors
	engine.buildMap();

	sf::RenderWindow window(sf::VideoMode(MAP_X * GRID_X, MAP_Y * GRID_Y), "AtjarMan");

	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	__load_assets(engine);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed :
					window.close();
					break ;
				default :
					break ;
			}
		}

		window.clear(sf::Color::Black); //Indicates Start Of Buffer

		engine.gameLogic();

		//Key Hooks (REMOVE DIZ SHIZ)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		//Do the temp renderz               DELETE THIS AFTERWARDS!!!! (DEBUG)
		__temp_render(engine, window);

		//Call all render logic here!

		window.display(); //Switch Buffers
	}

	return (0);
}

void	__load_assets(Engine &engine)
{
	engine.getPlayer().texture__.loadFromFile("images/slime.png");
	engine.getWallVector()[0].texture__.loadFromFile("images/wall.png");
	engine.getPlayer().sprite__.setTexture(engine.getPlayer().texture__);

	for (size_t i = 0; i < engine.getWallVector().size(); i++)
	{
		engine.getWallVector()[i].sprite__.setTexture(engine.getWallVector()[0].texture__);
	}
}

void	__temp_render(Engine &engine, sf::RenderWindow &window)
{
	engine.getPlayer().sprite__.setPosition(engine.getPlayer().getXPos(), engine.getPlayer().getYPos());
	engine.getPlayer().sprite__.setOrigin(24, 24);

	for (size_t i = 0; i < engine.getWallVector().size(); i++)
	{
		engine.getWallVector()[i].sprite__.setPosition(engine.getWallVector()[i].getXPos(), engine.getWallVector()[i].getYPos());
		engine.getWallVector()[i].sprite__.setOrigin(24, 24);
		window.draw(engine.getWallVector()[i].sprite__);
	}

	window.draw(engine.getPlayer().sprite__);
}
