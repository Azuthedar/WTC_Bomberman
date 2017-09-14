#include "../include/main.hpp"
#include "../include/AEntity.class.hpp"
#include "../include/Player.class.hpp"
#include "../include/GameEngine.class.hpp"
#include "../include/Wall.class.hpp"
#include "../include/Bomb.class.hpp"
#include "../../Graphics_lib/Inc/Render_Engine.hpp"
#include "../../Sound_lib/include/SoundEngine.hpp"

int main()
{
	try
	{

		
		Render_Engine render( "Atjar", 1280, 720);
		render.init();
		Engine engine;

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
				render.Create_Components( engine, deltaTime );
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

float distance_to_point(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
