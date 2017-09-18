#pragma once

#include "Base.hpp"

class Menu_Engine
{
    private:

        std::string window_name;
        int screen_height;
        int screen_width;

        static nanogui::Screen *base_screen;

        static MainMenu main_menu;
        static SettingsMenu settings_menu;

    public:

        Menu_Engine( std::string Win_Name );
        ~Menu_Engine();

        int update();
        void init();
        void gl_init();
        bool check_status();

        void createMainMenu();
        void createSettingsMenu();

        GLFWwindow *GetWindow() const;
};
