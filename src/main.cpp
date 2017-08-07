#include <main.hpp>
#include <AEntity.class.hpp>
#include <Player.class.hpp>
#include <GameEngine.class.hpp>
#include <Wall.class.hpp>
#include <Bomb.class.hpp>

void	__temp_render(Engine &engine, sf::RenderWindow &window, sf::Texture bombText, sf::Texture enemyText, sf::Texture explosionText);
void	__load_assets(Engine &engine);


int main(int argc, char **argv)
{
	sf::Texture bombText;
	sf::Texture enemyText;
	sf::Texture explosionText;
	bombText.loadFromFile("images/bomb.png");
	enemyText.loadFromFile("images/enemy.png");
	explosionText.loadFromFile("images/explosion.png");

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
	window.setFramerateLimit(FIXED_FPS);
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
		srand(time(NULL));
		engine.gameLogic();

		//Key Hooks (REMOVE DIZ SHIZ)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		//Do the temp renderz               DELETE THIS AFTERWARDS!!!! (DEBUG)
		__temp_render(engine, window, bombText, enemyText, explosionText);

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

void	__temp_render(Engine &engine, sf::RenderWindow &window, sf::Texture bombText, sf::Texture enemyText, sf::Texture explosionText)
{
	engine.getPlayer().sprite__.setPosition(engine.getPlayer().getXPos(), engine.getPlayer().getYPos());
	engine.getPlayer().sprite__.setOrigin(0, 48);

	for (size_t i = 0; i < engine.getPlayer().getBombVector().size(); i++)
	{
		engine.getPlayer().getBombVector()[i].sprite__.setTexture(bombText);
		engine.getPlayer().getBombVector()[i].sprite__.setPosition(engine.getPlayer().getBombVector()[i].getXPos(), engine.getPlayer().getBombVector()[i].getYPos());
		engine.getPlayer().getBombVector()[i].sprite__.setOrigin(0, 48);
		window.draw(engine.getPlayer().getBombVector()[i].sprite__);
	}

	for (size_t i = 0; i < engine.getWallVector().size(); i++)
	{
		engine.getWallVector()[i].sprite__.setPosition(engine.getWallVector()[i].getXPos(), engine.getWallVector()[i].getYPos());
		engine.getWallVector()[i].sprite__.setOrigin(0, 48);
		window.draw(engine.getWallVector()[i].sprite__);
	}

	for (size_t i = 0; i < engine.getEnemyVector().size(); i++)
	{
		engine.getEnemyVector()[i].sprite__.setTexture(enemyText);
		engine.getEnemyVector()[i].sprite__.setPosition(engine.getEnemyVector()[i].getXPos(), engine.getEnemyVector()[i].getYPos());
		engine.getEnemyVector()[i].sprite__.setOrigin(0, 48);
		window.draw(engine.getEnemyVector()[i].sprite__);
	}

	//Render Explosions (This one's nested because each bomb has it's own vector of explosions, so itterate through each bomb, then through it's respective explosions vector)
	for (size_t i = 0; i < engine.getPlayer().getBombVector().size(); i++)
	{
		for (size_t y = 0; y < engine.getPlayer().getBombVector()[i].getExplosionVector().size(); y++)
		{
			engine.getPlayer().getBombVector()[i].getExplosionVector()[y].sprite__.setTexture(explosionText);
			engine.getPlayer().getBombVector()[i].getExplosionVector()[y].sprite__.setPosition(engine.getPlayer().getBombVector()[i].getExplosionVector()[y].getXPos(), engine.getPlayer().getBombVector()[i].getExplosionVector()[y].getYPos());
			engine.getPlayer().getBombVector()[i].getExplosionVector()[y].sprite__.setOrigin(0, 48);
			window.draw(engine.getPlayer().getBombVector()[i].getExplosionVector()[y].sprite__);
		}
	}

	window.draw(engine.getPlayer().sprite__);
}