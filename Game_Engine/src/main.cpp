#include "../include/main.hpp"
#include "../include/AEntity.class.hpp"
#include "../include/Player.class.hpp"
#include "../include/GameEngine.class.hpp"
#include "../include/Wall.class.hpp"
#include "../include/Bomb.class.hpp"
#include "../../Graphics_lib/Inc/Render_Engine.hpp"
#include "../../Sound_lib/include/SoundEngine.hpp"
#include "../../Menu_lib/include/Menu_Engine.hpp"

int main()
{
	try
	{
		Menu_Engine menu( "Atjar" );

		Render_Engine render( menu.GetWindow() );

		Engine engine;
		
		GLfloat lastFrame = 0.0f;
		GLfloat deltaTime = 0.0f;
		GLfloat current_time = 0.0f;

		const double maxFPS = 60.0;
		const double maxPeriod = 1.0 / maxFPS;

		menu.set_data( engine );

		while ( !glfwWindowShouldClose( menu.GetWindow() ) )
		{
			std::srand(time(NULL));
			current_time = glfwGetTime();
			deltaTime += current_time - lastFrame;
			lastFrame = current_time;

			if ( deltaTime >= maxPeriod )
			{
				engine.gameLogic( menu.GetWindow(), deltaTime );
				glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
				glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

				glfwPollEvents();

				if (!menu.check_status())
				{
					render.Create_Components( engine );
					render._render( deltaTime );
				}

				if (menu.update( engine ))
				{
					render.SetWindow( menu.GetWindow() );
				}

				deltaTime = 0.0f;

				glfwSwapBuffers( menu.GetWindow() );
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
