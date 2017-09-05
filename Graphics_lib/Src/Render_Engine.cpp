#include "../Inc/Render_Engine.hpp"

GLFWwindow *Render_Engine::window = nullptr;
Camera *Render_Engine::camera = nullptr;

bool Render_Engine::firstmouse = true;
GLfloat Render_Engine::deltaTime = 0.0f;
GLfloat Render_Engine::lastFrame = 0.0f;

GLfloat Render_Engine::lastX = 0.0f;
GLfloat Render_Engine::lastY = 0.0f;

bool Render_Engine::keys[1024];

Render_Engine::Render_Engine()
{
    return ;
}

Render_Engine::Render_Engine( std::string Win_Name, int Win_Width, int Win_Height)
{
    this->Win_Name = Win_Name;
    this->Screen_Height = Win_Height;
    this->Screen_Width = Win_Width;
}

Render_Engine::~Render_Engine()
{
    return ;
}

GLFWwindow *Render_Engine::GetWindow() const
{
    return ( window );
}

void Render_Engine::load_dependencies()
{
    this->models.push_back( new Model("Graphics_lib/objects_and_textures/objFiles/model_Player.obj") );
    this->models.push_back( new Model("Graphics_lib/objects_and_textures/objFiles/bomb.obj") );
    this->models.push_back( new Model("Graphics_lib/objects_and_textures/objFiles/bug_EnemyHead.obj") );
    this->models.push_back( new Model("Graphics_lib/objects_and_textures/Crate/Crate1.obj") );
}

void Render_Engine::Create_Components( Engine &engine )
{
    this->components.push_back( new Component( "Player" , *this->models[0], 0.0f, 0.0f, 0.0f, 0.0f, 0.35f, glm::vec3( engine.getPlayer().getXPos() * 2 , 0.0f, engine.getPlayer().getYPos() * 2 ))  );

    /*for (size_t z = 1; z < MAP_Y + 1; z++)
    {
        for (size_t x = 0; x < MAP_X; x++)
        {
            this->components.push_back( new Component( "Platform", *this->models[1], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, glm::vec3( x * 2  , -1.0f, z * 2  ))  );
        }
    }*/

	for (size_t i = 0; i < engine.getPlayer().getBombVector().size(); i++)
	{
        this->components.push_back( new Component( "Bomb", *this->models[1], 0.0f, 0.0f, 0.0f, 0.0f, 2.5f, glm::vec3( engine.getPlayer().getBombVector()[i].getXPos() * 2 , 1.0f, engine.getPlayer().getBombVector()[i].getYPos() * 2 ))  );
  }


	for (size_t i = 0; i < engine.getWallVector().size(); i++)
	{
        this->components.push_back( new Component("Wall", *this->models[3], 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, glm::vec3( engine.getWallVector()[i].getXPos() * 2.0f, 1.0f, engine.getWallVector()[i].getYPos() * 2.0f ))  );
	}

	for (size_t i = 0; i < engine.getEnemyVector().size(); i++)
    {
        this->components.push_back( new Component("Enemy", *this->models[2], 0.0f, 0.0f, 0.0f, 0.0f, 0.55f, glm::vec3( engine.getEnemyVector()[i].getXPos() * 2 , 1.0f, engine.getEnemyVector()[i].getYPos() * 2 ))  );
	}

	//Render Explosions (This one's nested because each bomb has it's own vector of explosions, so itterate through each bomb, then through it's respective explosions vector)
	/*for (size_t i = 0; i < engine.getPlayer().getBombVector().size(); i++)
	{
		for (size_t y = 0; y < engine.getPlayer().getBombVector()[i].getExplosionVector().size(); y++)
		{
			engine.getPlayer().getBombVector()[i].getExplosionVector()[y].sprite__.setTexture(explosionText);
			engine.getPlayer().getBombVector()[i].getExplosionVector()[y].sprite__.setPosition(engine.getPlayer().getBombVector()[i].getExplosionVector()[y].getXPos(), engine.getPlayer().getBombVector()[i].getExplosionVector()[y].getYPos());
			engine.getPlayer().getBombVector()[i].getExplosionVector()[y].sprite__.setOrigin(0, 48);
			window.draw(engine.getPlayer().getBombVector()[i].getExplosionVector()[y].sprite__);
		}
	}*/
}

void Render_Engine::_render( GLfloat &tmp_delta_time )
{

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glm::vec3 player_pos =  this->components[0]->GetPosition();

    //while ( !glfwWindowShouldClose( Render_Engine::window ) )
    //{
        /*GLfloat current_time = glfwGetTime();
        Render_Engine::deltaTime = current_time - Render_Engine::lastFrame;
        Render_Engine::lastFrame = current_time;*/

        Render_Engine::deltaTime = tmp_delta_time;


        //std::cout << lastX << lastY << std::endl;

        glfwPollEvents( ); // poll for and process events
        //DoMovement();

        //test_func( (double)player_pos.x, -10.0);
        Render_Engine::camera->ProcessKeyboard( player_pos, deltaTime);


        glUseProgram( this->shader.GetProgramID() );

        this->draw.SetProjection( Render_Engine::camera->GetZoom() );

        this->draw.Prep();

        //projection = glm::perspective( Render_Engine::camera->GetZoom() , (GLfloat)this->Screen_Width / (GLfloat)this->Screen_Height, 1.0f, 10000.0f);

        //glm::mat4 model_matrix;
        //model_matrix = glm::rotate( model_matrix, (GLfloat)glfwGetTime() * 1.0f, glm::vec3( 0.5f, 1.0f, 0.0f ));
        //view_matrix = glm::translate( view_matrix, glm::vec3( 0.0f, 0.0f, -2.0f) );
        this->draw.SetViewMatrix( camera->GetViewMatrix() );

        //GLfloat angle = 20.0f * x;
        //model = glm::rotate( model, angle, glm::vec3( 0.0f, 0.0f, 0.0f ));

        this->draw.Render_( this->components, this->shader );

        glfwSwapBuffers( Render_Engine::window );
    //}

        //std::cout << "ysduyfgWGEFYWEFYIHWE " << std::endl;
}

void Render_Engine::init()
{
    if( !glfwInit() )
    {
        std::cout << "Bad news1" << std::endl;
        exit(1);
    }

    // open a window with GLFW, sets required GLFW options
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    Render_Engine::window = glfwCreateWindow( this->Screen_Width, this->Screen_Height, this->Win_Name.c_str(), nullptr, nullptr ); //Create GLFW window

    if ( !Render_Engine::window ) // Check if window was created
    {
        std::cout << "Bad news2" << std::endl;
        glfwTerminate(); // Terminate GLFW
        exit(2);
    }

    glfwMakeContextCurrent( Render_Engine::window ); // Make the windows context current
    glfwGetFramebufferSize( Render_Engine::window, &this->Screen_Width, &this->Screen_Height );

    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if( glewInit() != GLEW_OK )
    {
        std::cout << "Bad news 3" << std::endl;
        exit(3);
    }

    glfwSetKeyCallback( Render_Engine::window, KeyCallback);
    glfwSetScrollCallback( Render_Engine::window, ScrollCallback);
    glfwSetCursorPosCallback( Render_Engine::window, MouseCallback);

    glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

    Render_Engine::camera = new Camera( glm::vec3( 0.0f, 5.0f, 10.0f) );
    lastX = 0.0f;//this->Screen_Width / 2.0f;
    lastY = 0.0f;//this->Screen_Height / 2.0f;

    this->shader.compile_shaders("./Graphics_lib/Shaders/Colour_Shading.vert", "./Graphics_lib/Shaders/Colour_Shasiner.frag");

    load_dependencies();

    this->draw.Load_Uniform( this->shader );

    glViewport( 0.0f, 0.0f, this->Screen_Width, this->Screen_Height ); //this->Screen_Width, this->Screen_Height ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalized to pixels.



    //std::cout << "ysduyfgWGEFYWEFYIHWE " << std::endl;
}

void Render_Engine::test_func(  double posX, double posY  )
{
    std:: cout << " X1 " << posX << " Y1 " << posY << std::endl;

    /*if ( firstmouse )
    {
        lastX = posX;
        lastY = posY;
        firstmouse = false;
    }*/

    GLfloat xOffset = posX - lastX;
    GLfloat yOffset = lastY - posY;

    lastX = posX;
    lastY = posY;

    std:: cout << " X " << xOffset << " Y " << yOffset << std::endl;

    camera->ProcessMouseMovement( xOffset, yOffset );
}

void Render_Engine::KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose( window, GL_TRUE);

    if ( key >= 0 && key < 1024)
    {
        if ( GLFW_PRESS == action )
            keys[key] = true;
        else if ( GLFW_RELEASE == action )
            keys[key] = false;
    }
}

void Render_Engine::ScrollCallback( GLFWwindow *window, double xOffset, double yOffset )
{
    camera->ProcessMouseScroll( yOffset );
}

void Render_Engine::MouseCallback( GLFWwindow *window, double posX, double posY )
{
    //std:: cout << " X1 " << posX << " Y1 " << posY << std::endl;
    if ( firstmouse )
    {
        lastX = posX;
        lastY = posY;
        firstmouse = false;
    }

    GLfloat xOffset = posX - lastX;
    GLfloat yOffset = lastY - posY;

    lastX = posX;
    lastY = posY;

    //std:: cout << " X " << xOffset << " Y " << yOffset << std::endl;

    camera->ProcessMouseMovement( xOffset, yOffset );
}

/*void Render_Engine::DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
        camera->ProcessKeyboard( Camera_movement::FORWAR, deltaTime );
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
        camera->ProcessKeyboard( Camera_movement::BACKWAR, deltaTime );
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
        camera->ProcessKeyboard( Camera_movement::LEF, deltaTime );
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
        camera->ProcessKeyboard( Camera_movement::RIGH, deltaTime );
}*/
