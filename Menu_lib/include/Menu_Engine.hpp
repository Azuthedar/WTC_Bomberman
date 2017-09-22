#pragma once

#include "Base.hpp"

class Menu_Engine
{
    private:

        std::string window_name;
        static int screen_height;
        static int screen_width;

        static std::string window_mode;

        static nanogui::Screen *base_screen;

        static MainMenu main_menu;
        static SettingsMenu settings_menu;
        static PauseMenu pause_menu;
        static HUD hud;

        static Engine *engine;

        static bool isFullScreen;

        Data_Loader load;
        Shaders shader;
        std::vector < GLuint > texture_id;
        static std::vector < Texture > render_array;
        GLuint VAO, VBO;

        Exceptions excep;

        static int pos_min;
        static int pos_max;

        static std::unordered_map< std::string, int > key_binds;
        static std::unordered_map< std::string, int >::iterator it;

    public:

        Menu_Engine( std::string Win_Name );
        ~Menu_Engine();

        int update( Engine &engine );
        void init();
        void gl_init();
        bool check_status();
        void load_menu_textures();
        void render();

        void create_keyMaps();

        void set_data( Engine &temp_engine );

        void createMainMenu();
        void createSettingsMenu();
        void createPauseMenu();
        void createHUD();

        GLFWwindow *GetWindow() const;
};
