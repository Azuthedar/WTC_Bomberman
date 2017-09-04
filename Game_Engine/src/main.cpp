#include "../include/main.hpp"
#include "../include/AEntity.class.hpp"
#include "../include/Player.class.hpp"
#include "../include/GameEngine.class.hpp"
#include "../include/Wall.class.hpp"
#include "../include/Bomb.class.hpp"
#include "../../Graphics_lib/Inc/Render_Engine.hpp"

int main(int argc, char **argv)
{

	if (argc == 1)
	{
		return (0);
	}
	try
	{

		Engine engine;
		Render_Engine render( "Atjar", 1280, 720);

		engine.readFile(argv[1]);
		engine.readMap();
		//Load Map Into Respective Vectors
		engine.buildMap();


		render.init();

		GLfloat lastFrame = 0.0f;
		GLfloat deltaTime = 0.0f;
		GLfloat current_time = 0.0f;

		const double maxFPS = 60.0;
		const double maxPeriod = 1.0 / maxFPS;

		while ( !glfwWindowShouldClose( render.GetWindow() ) )
		{
			std::srand(time(NULL));
			current_time = glfwGetTime();
			deltaTime += current_time - lastFrame;
			lastFrame = current_time;

			if ( deltaTime >= maxPeriod )
			{
				engine.gameLogic( render.GetWindow(), deltaTime );
				render.Create_Components( engine );
				render._render( deltaTime );
				deltaTime = 0.0f;
			}
		}

	}
	catch (std::exception & e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return (0);
}

/*void	__load_assets(Engine &engine)
{
	engine.getPlayer().texture__.loadFromFile("images/slime.png");
	engine.getWallVector()[0].texture__.loadFromFile("images/wall.png");
	engine.getPlayer().sprite__.setTexture(engine.getPlayer().texture__);
	engine.getWallVector()[1].texture__.loadFromFile("images/brokenwall.png");

	for (size_t i = 0; i < engine.getWallVector().size(); i++)
	{
		if (engine.getWallVector()[i].getBlockType() == SOLID_BLOCK)
			engine.getWallVector()[i].sprite__.setTexture(engine.getWallVector()[0].texture__);
		else if (engine.getWallVector()[i].getBlockType() == DESTRUCTIBLE_BLOCK || engine.getWallVector()[i].getBlockType() == GATE)
			engine.getWallVector()[i].sprite__.setTexture(engine.getWallVector()[1].texture__);
	}
}

void	__temp_render(Engine &engine, sf::RenderWindow &window, sf::Texture bombText, sf::Texture enemyText, sf::Texture explosionText, sf::Texture lifePowerup, sf::Texture bombPowerup, sf::Texture rangePowerup, sf::Texture speedPowerup, sf::Texture gate)
{
	engine.getPlayer().sprite__.setPosition(engine.getPlayer().getXPos(), engine.getPlayer().getYPos());
	engine.getPlayer().sprite__.setOrigin(0, 48);

	if (engine.getGate().getExists())
	{
		engine.getGate().sprite__.setTexture(gate);
		engine.getGate().sprite__.setPosition(engine.getGate().getXPos(), engine.getGate().getYPos());
		engine.getGate().sprite__.setOrigin(0, 48);
		window.draw(engine.getGate().sprite__);
	}

	for (size_t i = 0; i < engine.getPlayer().getBombVector().size(); i++)
	{
		engine.getPlayer().getBombVector()[i].sprite__.setTexture(bombText);
		engine.getPlayer().getBombVector()[i].sprite__.setPosition(engine.getPlayer().getBombVector()[i].getXPos(), engine.getPlayer().getBombVector()[i].getYPos());
		engine.getPlayer().getBombVector()[i].sprite__.setOrigin(0, 48);
		if (engine.getPlayer().getBombVector()[i].getExploded() == false)
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

	for (size_t i = 0; i < engine.getPowerupVector().size(); i++)
	{
		if (engine.getPowerupVector()[i].getTypePowerup() == POW_LIFE)
		{
			engine.getPowerupVector()[i].sprite__.setTexture(lifePowerup);
			engine.getPowerupVector()[i].sprite__.setPosition(engine.getPowerupVector()[i].getXPos(), engine.getPowerupVector()[i].getYPos());
			engine.getPowerupVector()[i].sprite__.setOrigin(0, 48);
		}
		else if (engine.getPowerupVector()[i].getTypePowerup() == POW_BOMBS)
		{
			engine.getPowerupVector()[i].sprite__.setTexture(bombPowerup);
			engine.getPowerupVector()[i].sprite__.setPosition(engine.getPowerupVector()[i].getXPos(), engine.getPowerupVector()[i].getYPos());
			engine.getPowerupVector()[i].sprite__.setOrigin(0, 48);
		}
		else if (engine.getPowerupVector()[i].getTypePowerup() == POW_SPEED)
		{
			engine.getPowerupVector()[i].sprite__.setTexture(speedPowerup);
			engine.getPowerupVector()[i].sprite__.setPosition(engine.getPowerupVector()[i].getXPos(), engine.getPowerupVector()[i].getYPos());
			engine.getPowerupVector()[i].sprite__.setOrigin(0, 48);

		}
		else if (engine.getPowerupVector()[i].getTypePowerup() == POW_RANGE)
		{
			engine.getPowerupVector()[i].sprite__.setTexture(rangePowerup);
			engine.getPowerupVector()[i].sprite__.setPosition(engine.getPowerupVector()[i].getXPos(), engine.getPowerupVector()[i].getYPos());
			engine.getPowerupVector()[i].sprite__.setOrigin(0, 48);
		}
		window.draw(engine.getPowerupVector()[i].sprite__);
	}

	window.draw(engine.getPlayer().sprite__);
}*/


float distance_to_point(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
