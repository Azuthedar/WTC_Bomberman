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

        Exceptions excep;

        static GLFWwindow *window;
        static Camera *camera;

        static GLfloat lastX;
        static GLfloat lastY;

        static bool keys[1024];
        static bool firstmouse ;

        static GLfloat deltaTime;
        static GLfloat lastFrame;

        static int tmp_test;

        Render draw;
        Data_Loader load;
        Shaders shader;
        Shaders SkyBox_shader;
        Shaders Particle_shader;
        Particle_manager *particle_manager;

        std::vector < Model * > models;
        std::vector < Component * > components;
        std::vector < Model * > player_models;

        Skybox_s Skybox;
        Particles_s particle_data;

        Render_Engine();

    public:

        Render_Engine( GLFWwindow *tmp_window );
        ~Render_Engine();

        Render_Engine(Render_Engine const &src);
        Render_Engine &operator=(Render_Engine const &rhs);

        void init();
        void _render( GLfloat &tmp_delta_time );

        void load_dependencies();
        void load_Shaders();
        void clean_dependencies();

        void SetWindow( GLFWwindow *tmp_window );

        void Create_Components( Engine &engine );

        static void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods);
        static void ScrollCallback( GLFWwindow *window, double xOffset, double yOffset );
        static void MouseCallback( GLFWwindow *window, double posX, double posY );
        void test_func(  double posX, double posY  );
        //void DoMovement();

        const std::string &getWin_Name() const;
        int getScreen_Width() const;
        int getScreen_Height() const;
        static GLFWwindow *getWindow();
        static Camera *getCamera();
        static GLfloat getLastX();
        static GLfloat getLastY();
        static bool *getKeys();
        static bool isFirstmouse();
        static GLfloat getDeltaTime();
        static GLfloat getLastFrame();
        static int getTmp_test();
        const Render &getDraw() const;
        const Data_Loader &getLoad() const;
        const Shaders &getShader() const;
        const Shaders &getSkyBox_shader() const;
        const Shaders &getParticle_shader() const;
        Particle_manager *getParticle_manager() const;
        const std::vector<Model *> &getModels() const;
        const std::vector<Component *> &getComponents() const;
        const std::vector<Model *> &getPlayer_models() const;
        const Skybox_s &getSkybox() const;
        const Particles_s &getParticle_data() const;
};
