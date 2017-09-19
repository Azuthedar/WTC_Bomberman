#pragma once


#include "../../Game_Engine/include/GameEngine.class.hpp"
#include "../nanogui/include/nanogui/screen.h"
#include "../nanogui/include/nanogui/window.h"
#include "../nanogui/include/nanogui/layout.h"
#include "../nanogui/include/nanogui/button.h"

#include "../nanogui/include/nanogui/opengl.h"
#include "../nanogui/include/nanogui/glutil.h"
#include "../nanogui/include/nanogui/screen.h"
#include "../nanogui/include/nanogui/window.h"
#include "../nanogui/include/nanogui/layout.h"
#include "../nanogui/include/nanogui/label.h"
#include "../nanogui/include/nanogui/checkbox.h"
#include "../nanogui/include/nanogui/button.h"
#include "../nanogui/include/nanogui/toolbutton.h"
#include "../nanogui/include/nanogui/popupbutton.h"
#include "../nanogui/include/nanogui/combobox.h"
#include "../nanogui/include/nanogui/progressbar.h"
#include "../nanogui/include/nanogui/entypo.h"
#include "../nanogui/include/nanogui/textbox.h"
#include "../nanogui/include/nanogui/messagedialog.h"
#include "../nanogui/include/nanogui/slider.h"
#include "../nanogui/include/nanogui/imagepanel.h"
#include "../nanogui/include/nanogui/imageview.h"
#include "../nanogui/include/nanogui/vscrollpanel.h"
#include "../nanogui/include/nanogui/colorwheel.h"
#include "../nanogui/include/nanogui/graph.h"
#include "../nanogui/include/nanogui/tabwidget.h"

#include <GLFW/glfw3.h>
#include "../nanogui/include/nanogui/nanogui.h"

#include <cstdint>
#include <memory>
#include <utility>
#include <map>
#include <unordered_map>

#include <iostream>

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

    nanogui::PopupButton *KeyBinds = nullptr;
    nanogui::Popup *keybind_popup = nullptr;

    nanogui::Theme   *theme;

    nanogui::Button *Button_Up;
    nanogui::Button *Button_Down;
    nanogui::Button *Button_Left;
    nanogui::Button *Button_Right;
    nanogui::Button *Button_Place;

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
