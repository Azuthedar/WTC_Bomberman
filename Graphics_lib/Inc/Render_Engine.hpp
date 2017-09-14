#pragma once

#include "Base.hpp"
#include "Render.hpp"
#include "Model.hpp"
#include "Shaders.hpp"
#include "Camera.hpp"
#include "Component.hpp"
#include "Light_class.hpp"
#include "Particle_manager.hpp"
#include "../../Game_Engine/include/GameEngine.class.hpp"

class Render_Engine
{
    private:

        std::string Win_Name;
        int Screen_Width;
        int Screen_Height;

        static GLFWwindow *window;
        static Camera *camera;

        static GLfloat lastX;
        static GLfloat lastY;

        static bool keys[1024];
        static bool firstmouse ;

        static GLfloat deltaTime;
        static GLfloat lastFrame;

        Render draw;
        Shaders shader;
        Shaders SkyBox_shader;
        Shaders Particle_shader;
        Particle_manager *particle_manager;

        std::vector < Model * > models;
        std::vector < Component * > components;

        Skybox_s Skybox;
        Particles_s particle_data;

        Render_Engine();

    public:

        Render_Engine( std::string Win_Name, int Win_Width, int Win_Height);
        ~Render_Engine();

        void init();
        void _render( GLfloat &tmp_delta_time );

        GLFWwindow *GetWindow() const;
        void load_dependencies();

        void Create_Components( Engine &engine, GLfloat &tmp_delta_time );

        static void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods);
        static void ScrollCallback( GLFWwindow *window, double xOffset, double yOffset );
        static void MouseCallback( GLFWwindow *window, double posX, double posY );
        void test_func(  double posX, double posY  );
        //void DoMovement();

};