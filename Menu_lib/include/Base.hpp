#pragma once

//Comment out clear funtion in screen.cpp -> DrawAll() 

#include "../../Graphics_lib/Inc/Data_Loader.hpp"
#include "../../Graphics_lib/Inc/Shaders.hpp"

#include "../../Game_Engine/include/GameEngine.class.hpp"
#include "../../Libs/nanogui/include/nanogui/screen.h"
#include "../../Libs/nanogui/include/nanogui/window.h"
#include "../../Libs/nanogui/include/nanogui/layout.h"
#include "../../Libs/nanogui/include/nanogui/button.h"

#include "../../Libs/nanogui/include/nanogui/opengl.h"
#include "../../Libs/nanogui/include/nanogui/glutil.h"
#include "../../Libs/nanogui/include/nanogui/screen.h"
#include "../../Libs/nanogui/include/nanogui/window.h"
#include "../../Libs/nanogui/include/nanogui/layout.h"
#include "../../Libs/nanogui/include/nanogui/label.h"
#include "../../Libs/nanogui/include/nanogui/checkbox.h"
#include "../../Libs/nanogui/include/nanogui/button.h"
#include "../../Libs/nanogui/include/nanogui/toolbutton.h"
#include "../../Libs/nanogui/include/nanogui/popupbutton.h"
#include "../../Libs/nanogui/include/nanogui/combobox.h"
#include "../../Libs/nanogui/include/nanogui/progressbar.h"
#include "../../Libs/nanogui/include/nanogui/entypo.h"
#include "../../Libs/nanogui/include/nanogui/textbox.h"
#include "../../Libs/nanogui/include/nanogui/messagedialog.h"
#include "../../Libs/nanogui/include/nanogui/slider.h"
#include "../../Libs/nanogui/include/nanogui/imagepanel.h"
#include "../../Libs/nanogui/include/nanogui/imageview.h"
#include "../../Libs/nanogui/include/nanogui/vscrollpanel.h"
#include "../../Libs/nanogui/include/nanogui/colorwheel.h"
#include "../../Libs/nanogui/include/nanogui/graph.h"
#include "../../Libs/nanogui/include/nanogui/tabwidget.h"

#include <GLFW/glfw3.h>
#include "../../Libs/nanogui/include/nanogui/nanogui.h"

#include <cstdint>
#include <memory>
#include <utility>
#include <map>
#include <unordered_map>

#include <iostream>

struct PauseMenu
{
    nanogui::Window *pauseMenu_window = nullptr;
    nanogui::Button *b_continue = nullptr;
    nanogui::Button *b_settings = nullptr;
    nanogui::Button *b_exit = nullptr;

    PauseMenu() = default;

        void    changeView(bool value)
        {
            if (pauseMenu_window != nullptr)
                pauseMenu_window->setVisible(value);
        }
};

struct  MainMenu
{
    nanogui::Window  *mainMenu_window = nullptr;
    nanogui::Button  *start = nullptr;
    nanogui::Button  *settings = nullptr;
    nanogui::Button  *exit_game = nullptr;
    nanogui::Button  *load_game = nullptr;
    nanogui::Theme   *theme;

    MainMenu() = default;

    void    changeView(bool value)
    {
        if (mainMenu_window != nullptr)
            mainMenu_window->setVisible(value);
    }
};

struct  SettingsMenu
{
    nanogui::Window  *settingsMenu_window = nullptr;

    nanogui::Button  *res_720 = nullptr;
    nanogui::Button  *res_1080 = nullptr;
    nanogui::Button  *back_button = nullptr;

    nanogui::Slider  *vol_slider = nullptr;
    nanogui::Slider  *sfx_volume = nullptr;

    nanogui::PopupButton *KeyBinds = nullptr;
    nanogui::Popup *keybind_popup = nullptr;

    nanogui::Theme   *theme;

    nanogui::Button *Button_Up;
    nanogui::Button *Button_Down;
    nanogui::Button *Button_Left;
    nanogui::Button *Button_Right;
    nanogui::Button *Button_Place;
    nanogui::Button *Window_Mode = nullptr;

    nanogui::Button *Apply;

    int new_key = 0;

    bool bind_change = false;

    int button_type = 0;

    int curr_up = 0;
    int curr_down = 0;
    int curr_Left = 0;
    int curr_Right = 0;
    int curr_place = 0;

    nanogui::TextBox *key_textBox;

    int res_type = 0;
    bool res_change = false;

    SettingsMenu() = default;

    void    changeView(bool value)
    {
        if (settingsMenu_window != nullptr)
            settingsMenu_window->setVisible(value);
    }
};
