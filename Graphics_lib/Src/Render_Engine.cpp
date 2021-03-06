#include "../Inc/Render_Engine.hpp"

GLFWwindow *Render_Engine::window = nullptr;
Camera *Render_Engine::camera = nullptr;

bool Render_Engine::firstmouse = true;
GLfloat Render_Engine::deltaTime = 0.0f;
GLfloat Render_Engine::lastFrame = 0.0f;

GLfloat Render_Engine::lastX = 0.0f;
GLfloat Render_Engine::lastY = 0.0f;

int Render_Engine::tmp_test = 0;

bool Render_Engine::keys[1024];

Render_Engine::Render_Engine()
{
    return ;
}

Render_Engine::Render_Engine( GLFWwindow *tmp_window )
{
    Render_Engine::window = tmp_window;
    init();
}

Render_Engine::~Render_Engine()
{
    return ;
}

void Render_Engine::clean_dependencies()
{
    if ( this->models.size() > 0)
    {
        for (unsigned int count = 0; count < this->models.size(); count++)
        {
            delete this->models[count];
        }

        for (unsigned int count = 0; count < this->player_models.size(); count++)
        {
            delete this->player_models[count];
        }

        this->models.clear();
        this->player_models.clear();
    }
}

void Render_Engine::SetWindow( GLFWwindow *tmp_window )
{
    Render_Engine::window = tmp_window;

    load_Shaders();
    clean_dependencies();
    load_dependencies();
}

void Render_Engine::load_dependencies()
{
    std::vector< std::string > faces;
    faces.push_back( "Assets/objects_and_textures/Skybox/GameSkyBox01_right.png" ); // Positive X == Right Face
    faces.push_back( "Assets/objects_and_textures/Skybox/GameSkyBox01_left.png" ); // Negative X == Left Face
    faces.push_back( "Assets/objects_and_textures/Skybox/GameSkyBox01_down.png" ); // Positive Y == Top Face
    faces.push_back( "Assets/objects_and_textures/Skybox/GameSkyBox01_up.png" ); // Negative Y == Bottom Face
    faces.push_back( "Assets/objects_and_textures/Skybox/GameSkyBox01_back.png" ); // Positive Z == Back Face
    faces.push_back( "Assets/objects_and_textures/Skybox/GameSkyBox01_front.png" ); // Negative Z == Front Face

    this->models.push_back( new Model("Assets/objects_and_textures/objFiles/bomb.obj", 1) ); //0
    this->models.push_back( new Model("Assets/objects_and_textures/objFiles/bug_EnemyHead.obj", 1) ); //1
    this->models.push_back( new Model("Assets/objects_and_textures/Crate/Crate1.obj", 3) ); //2
    this->models.push_back( new Model("Assets/objects_and_textures/objFiles/robot_EnemyHead.obj", 1) ); //3
    this->models.push_back( new Model("Assets/objects_and_textures/objFiles/model_lock_gate.obj", 1)); //4
    this->models.push_back( new Model("Assets/objects_and_textures/objFiles/gate.obj", 1)); //5
    this->models.push_back( new Model("Assets/objects_and_textures/objFiles/Plane.obj", 1)); //6

    this->player_models.push_back( new Model("Assets/objects_and_textures/player_run_anim/Player1.obj", 1) );
    this->player_models.push_back( new Model("Assets/objects_and_textures/player_run_anim/Player2.obj", 1) );
    this->player_models.push_back( new Model("Assets/objects_and_textures/player_run_anim/Player3.obj", 1) );
    this->player_models.push_back( new Model("Assets/objects_and_textures/player_run_anim/Player4.obj", 1) );
    this->player_models.push_back( new Model("Assets/objects_and_textures/player_run_anim/Player5.obj", 1) );
    this->player_models.push_back( new Model("Assets/objects_and_textures/player_run_anim/Player6.obj", 1) );

    Model tmp_load;
    this->Skybox = tmp_load.loadSkybox( faces );
    this->particle_data = tmp_load.loadParticle( );

    Texture Tmp_texture;
    struct Texture
    {
        GLuint id;
        std::string type;
        aiString path;
        int num_rows;
        int num_columns;
    };
    this->particle_data.Particle_text = this->load.load_texture( "explosion_atlas.png" , "Assets/objects_and_textures");

    Tmp_texture.id = this->particle_data.Particle_text;
    Tmp_texture.type = "atlas";
    Tmp_texture.path = "Graphics_lib/objects_and_textures/";
    Tmp_texture.num_rows = ATLAS_R;
    Tmp_texture.num_columns = ATLAS_C;

    this->particle_manager->SetTexture( Tmp_texture );
}

void Render_Engine::Create_Components( Engine &engine )
{
    if ( engine.getIsTransitioning() == false )
    {
        if ( tmp_test >= 18 )
            tmp_test = 0;

        int frame = 0;
        if (engine.getPlayer().getIsMoving())
        {
            tmp_test++;
            frame = (tmp_test - 1) / 3;
        }

        this->components.push_back( new Component( "Player" , this->player_models[frame], 0.0f, engine.getPlayer().getDir(), 0.35f, glm::vec3( engine.getPlayer().getXPos() * 2 , 0.0f, engine.getPlayer().getYPos() * 2 ), 0)  );

        for (int y = 1; y < MAP_Y; y++)
        {
            for (int x = 0; x < MAP_X; x++)
            {
                this->components.push_back( new Component("Plane", this->models[6], 0.0f, -1, 1.0f, glm::vec3( x * 2.0f, 0.0f, y * 2.0f ), 0)  );
            }
        }
    }

    for (size_t i = 0; i < engine.getPlayer().getBombVector().size(); i++)
  	{
        this->components.push_back( new Component( "Bomb", this->models[0], 0.0f, -1, 2.5f , glm::vec3( engine.getPlayer().getBombVector()[i].getXPos() * 2 , 1.0f, engine.getPlayer().getBombVector()[i].getYPos() * 2 ), 0)  );
    }

  	for (size_t i = 0; i < engine.getWallVector().size(); i++)
  	{
        if (engine.getWallVector()[i].getBlockType() == SOLID_BLOCK)
            this->components.push_back( new Component("Wall", this->models[2], 0.0f, -1, 1.0f, glm::vec3( engine.getWallVector()[i].getXPos() * 2.0f, 1.0f, engine.getWallVector()[i].getYPos() * 2.0f ), 0)  );
        else if (engine.getWallVector()[i].getBlockType() == DESTRUCTIBLE_BLOCK || engine.getWallVector()[i].getBlockType() == GATE)
            this->components.push_back( new Component("Destructibe_Wall", this->models[2], 0.0f, -1, 1.0f, glm::vec3( engine.getWallVector()[i].getXPos() * 2.0f, 1.0f, engine.getWallVector()[i].getYPos() * 2.0f ), 5)  );
  	}

  	for (size_t i = 0; i < engine.getEnemyVector().size(); i++)
    {
        if ( engine.getEnemyVector()[i].getType() == BUG)
            this->components.push_back( new Component("Enemy", this->models[1], 0.0f, engine.getEnemyVector()[i].getDir(), 0.55f, glm::vec3( engine.getEnemyVector()[i].getXPos() * 2 , engine.getEnemyVector()[i].getZPos(), engine.getEnemyVector()[i].getYPos() * 2 ), 0)  );
        else if ( engine.getEnemyVector()[i].getType() == ROBOT)
            this->components.push_back( new Component("Enemy", this->models[3], 0.0f, engine.getEnemyVector()[i].getDir(), 0.55f, glm::vec3( engine.getEnemyVector()[i].getXPos() * 2 , engine.getEnemyVector()[i].getZPos(), engine.getEnemyVector()[i].getYPos() * 2 ), 0)  );
  	}

    //Push back floaty bloos
    glm::vec3 npos = glm::vec3( 0.0f );
    this->particle_manager->Generate_Particles( npos, 0.0f);

    if (engine.getGate().getExists() && engine.getGate().getIsLocked())
    {
        this->components.push_back( new Component("Locked_Gate", this->models[4], 0.0f, -1, 2.0f, glm::vec3( engine.getGate().getXPos() * 2.0f, 0.1f, engine.getGate().getYPos() * 2.0f ), 0)  );
    }
    else if (engine.getGate().getExists() && !engine.getGate().getIsLocked())
    {
        glm::vec3 pos = glm::vec3( 0.0f );
        pos.x =  engine.getGate().getXPos() * 2.0f;
        pos.z =  engine.getGate().getYPos() * 2.0f;
        this->components.push_back( new Component("Unlocked_Gate", this->models[5], 0.0f, -1, 2.0f, glm::vec3( engine.getGate().getXPos() * 2.0f, 0.1f,  engine.getGate().getYPos() * 2.0f ), 0)  );
        this->particle_manager->Generate_Particles( pos, 69);
    }

    for (size_t i = 0; i < engine.getPowerupVector().size(); i++)
  	{
		if (engine.getPowerupVector()[i].getTypePowerup() == POW_LIFE)
		{
            this->components.push_back( new Component("Pow_Life", this->models[2], -2.0f, -1, 0.4f, glm::vec3( engine.getPowerupVector()[i].getXPos() * 2.0f, 1.5f, engine.getPowerupVector()[i].getYPos() * 2.0f ), 2)  );
		}
		else if (engine.getPowerupVector()[i].getTypePowerup() == POW_BOMBS)
		{
			this->components.push_back( new Component("Pow_Bomb", this->models[2], 2.0f, -1, 0.4f, glm::vec3( engine.getPowerupVector()[i].getXPos() * 2.0f, 1.5f, engine.getPowerupVector()[i].getYPos() * 2.0f ), 1)  );
		}
		else if (engine.getPowerupVector()[i].getTypePowerup() == POW_SPEED)
		{
			this->components.push_back( new Component("Pow_Speed", this->models[2], -2.0f, -1, 0.4f, glm::vec3( engine.getPowerupVector()[i].getXPos() * 2.0f, 1.5f, engine.getPowerupVector()[i].getYPos() * 2.0f ), 4)  );
		}
		else if (engine.getPowerupVector()[i].getTypePowerup() == POW_RANGE)
		{
            this->components.push_back( new Component("Pow_Range", this->models[2], 2.0f, -1, 0.4f, glm::vec3( engine.getPowerupVector()[i].getXPos() * 2.0f, 1.5f, engine.getPowerupVector()[i].getYPos() * 2.0f ), 3)  );
		}
  	}

    glm::vec3 pos = glm::vec3( 0.0f );
    for (size_t i = 0; i < engine.getPlayer().getBombVector().size(); i++)
  	{
  		for (size_t y = 0; y < engine.getPlayer().getBombVector()[i].getExplosionVector().size(); y++)
  		{
            pos.x = engine.getPlayer().getBombVector()[i].getExplosionVector()[y].getXPos() * 2;
            pos.z =  engine.getPlayer().getBombVector()[i].getExplosionVector()[y].getYPos() * 2;

            this->particle_manager->Generate_Particles( pos );
  		}
  	}
}

void Render_Engine::_render( GLfloat &tmp_delta_time )
{
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_BLEND );
    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glm::vec3 player_pos = glm::vec3( 0.0f, 0.0f, 0.0f);
    if ( this->components.size() > 0 )
        player_pos = this->components[0]->GetPosition();

    Render_Engine::deltaTime = tmp_delta_time;
    this->particle_manager->manage_particles( tmp_delta_time );

    Render_Engine::camera->ProcessKeyboard( player_pos );


    glUseProgram( this->shader.GetProgramID() );

    this->draw.SetProjection( Render_Engine::camera->GetZoom() );


    this->draw.SetViewMatrix( camera->GetViewMatrix() );



    this->draw.Render_( this->components, this->shader );
    this->draw.Render_Particles( this->particle_manager->GetParticleArray(), this->Particle_shader, this->particle_data );
    this->draw.Render_Skybox( this->Skybox, this->SkyBox_shader );

    glDisable( GL_DEPTH_TEST );
    glDisable( GL_BLEND );
    glDisable( GL_CULL_FACE );
}

void Render_Engine::load_Shaders()
{
    this->shader.unuse_prog();
    this->SkyBox_shader.unuse_prog();
    this->Particle_shader.unuse_prog();

    std::cout << "Base Shader" << std::endl;
    this->shader.compile_shaders("./Graphics_lib/Shaders/Colour_Shading.vert", "./Graphics_lib/Shaders/Colour_Shasiner.frag");
    std::cout << "Skybox Shader" << std::endl;
    this->SkyBox_shader.compile_shaders("./Graphics_lib/Shaders/skybox.vert", "./Graphics_lib/Shaders/skybox.frag");
    std::cout << "Particle Shader" << std::endl;
    this->Particle_shader.compile_shaders("./Graphics_lib/Shaders/Particle.vert", "./Graphics_lib/Shaders/Particle.frag");

    this->draw.Load_Uniform( this->shader );
}

void Render_Engine::init()
{
    Render_Engine::camera = new Camera( glm::vec3( 0.0f, 5.0f, 10.f) );

    this->particle_manager = new Particle_manager( 4.0f, 25.0f, 0.0f, 1.0f );

    load_Shaders();

    load_dependencies();
}

Render_Engine::Render_Engine(Render_Engine const &src) {
    *this = src;
    return ;
}

Render_Engine &Render_Engine::operator=(Render_Engine const &rhs) {
    this->Win_Name = rhs.getWin_Name();
    this->Screen_Width = rhs.getScreen_Width();
    this->Screen_Height = rhs.getScreen_Height();
    this->window = rhs.getWindow();
    this->camera = rhs.getCamera();
    this->lastX = rhs.getLastX();
    this->lastY = rhs.getLastY();
    this->firstmouse = rhs.isFirstmouse();
    this->deltaTime = rhs.getDeltaTime();
    this->lastFrame = rhs.getLastFrame();
    this->tmp_test = rhs.getTmp_test();
    this->draw = rhs.getDraw();
    this->load = rhs.getLoad();
    this->shader = rhs.getShader();
    this->SkyBox_shader = rhs.getSkyBox_shader();
    this->Skybox = rhs.getSkybox();
    this->particle_manager = rhs.getParticle_manager();
    this->Particle_shader = rhs.getParticle_shader();
    this->models = rhs.getModels();
    this->components = rhs.getComponents();
    this->player_models = rhs.getPlayer_models();
    this->particle_data = rhs.getParticle_data();

    return *this;
}

const std::string &Render_Engine::getWin_Name() const { return Win_Name; }
int Render_Engine::getScreen_Width() const { return Screen_Width;}
int Render_Engine::getScreen_Height() const { return Screen_Height; }
GLFWwindow *Render_Engine::getWindow() { return window; }
Camera *Render_Engine::getCamera() { return camera; }
GLfloat Render_Engine::getLastX() { return lastX; }
GLfloat Render_Engine::getLastY() { return lastY; }
bool *Render_Engine::getKeys() { return keys; }
bool Render_Engine::isFirstmouse() { return firstmouse; }
GLfloat Render_Engine::getDeltaTime() { return deltaTime; }
GLfloat Render_Engine::getLastFrame() { return lastFrame; }
int Render_Engine::getTmp_test() { return tmp_test; }
const Render &Render_Engine::getDraw() const { return draw; }
const Data_Loader &Render_Engine::getLoad() const { return load; }
const Shaders &Render_Engine::getShader() const { return shader; }
const Shaders &Render_Engine::getSkyBox_shader() const { return SkyBox_shader; }
const Shaders &Render_Engine::getParticle_shader() const { return Particle_shader; }
Particle_manager *Render_Engine::getParticle_manager() const { return particle_manager; }
const std::vector<Model *> &Render_Engine::getModels() const { return models; }
const std::vector<Component *> &Render_Engine::getComponents() const { return components; }
const std::vector<Model *> &Render_Engine::getPlayer_models() const { return player_models; }
const Skybox_s &Render_Engine::getSkybox() const { return Skybox; }
const Particles_s &Render_Engine::getParticle_data() const { return particle_data; }
