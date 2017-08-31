#pragma once

#include "Base.hpp"
#include "Data_Loader.hpp"
#include "Render.hpp"
#include "Model.hpp"
#include "Shaders.hpp"
#include "Model_Text.hpp"
#include "Text_Model.hpp"
#include "Object_Loader.hpp"
#include "Camera.hpp"
#include "Component.hpp"
#include "Light_class.hpp"
#include "../../include/GameEngine.class.hpp"

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

        Data_Loader load;
        Object_Loader obj_load;
        Render draw;
        Shaders shader;

        std::vector < Model * > models;
        std::vector < Model_Text * > textures;
        std::vector < Text_Model * > text_model;
        std::vector < Component * > components;

        Render_Engine();

    public:

        Render_Engine( std::string Win_Name, int Win_Width, int Win_Height);
        ~Render_Engine();

        void init();
        void _render( GLfloat &tmp_delta_time );

        GLFWwindow *GetWindow() const;
        void load_dependencies();

        void Create_Components( Engine &engine );

        static void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mods);
        static void ScrollCallback( GLFWwindow *window, double xOffset, double yOffset );
        static void MouseCallback( GLFWwindow *window, double posX, double posY );
        void test_func(  double posX, double posY  );
        //void DoMovement();

};
