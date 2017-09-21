#include "../include/Menu_Engine.hpp"

nanogui::Screen *Menu_Engine::base_screen = nullptr;
MainMenu Menu_Engine::main_menu = MainMenu();
SettingsMenu Menu_Engine::settings_menu = SettingsMenu();
PauseMenu Menu_Engine::pause_menu = PauseMenu();


Engine  *Menu_Engine::engine = nullptr;

std::unordered_map< std::string, int > Menu_Engine::key_binds;
std::unordered_map< std::string, int >::iterator Menu_Engine::it;

Menu_Engine::Menu_Engine( std::string Win_Name )
{
    this->window_name = Win_Name;
    this->screen_width = 1280;
    this->screen_height = 720;

    init();
    create_keyMaps();
}

void Menu_Engine::set_data( Engine &temp_engine )
{
    engine = &temp_engine;

    settings_menu.curr_up = engine->getConfig().getKBMoveUp();
    settings_menu.curr_down = engine->getConfig().getKBMoveDown();
    settings_menu.curr_Left = engine->getConfig().getKBMoveLeft();
    settings_menu.curr_Right = engine->getConfig().getKBMoveRight();
    settings_menu.curr_place = engine->getConfig().getKBPlaceBomb();
}

void Menu_Engine::create_keyMaps()
{
    key_binds.insert( std::make_pair( "F1", GLFW_KEY_F1 ) );
    key_binds.insert( std::make_pair( "F2", GLFW_KEY_F2 ) );
	key_binds.insert( std::make_pair( "F3", GLFW_KEY_F3 ) );
	key_binds.insert( std::make_pair( "F4", GLFW_KEY_F4 ) );
	key_binds.insert( std::make_pair( "F5", GLFW_KEY_F5 ) );
	key_binds.insert( std::make_pair( "F6", GLFW_KEY_F6 ) );
	key_binds.insert( std::make_pair( "F7", GLFW_KEY_F7 ) );
	key_binds.insert( std::make_pair( "F8", GLFW_KEY_F8 ) );
	key_binds.insert( std::make_pair( "F9", GLFW_KEY_F9 ) );
	key_binds.insert( std::make_pair( "F10", GLFW_KEY_F10 ) );
	key_binds.insert( std::make_pair( "F11", GLFW_KEY_F11 ) );
	key_binds.insert( std::make_pair( "F12", GLFW_KEY_F12 ) );
	key_binds.insert( std::make_pair( "F13", GLFW_KEY_F13 ) );
	key_binds.insert( std::make_pair( "F14", GLFW_KEY_F14 ) );
	key_binds.insert( std::make_pair( "F15", GLFW_KEY_F15 ) );
	key_binds.insert( std::make_pair( "UP", GLFW_KEY_UP ) );
	key_binds.insert( std::make_pair( "DOWN", GLFW_KEY_DOWN ) );
	key_binds.insert( std::make_pair( "LEFT", GLFW_KEY_LEFT ) );
	key_binds.insert( std::make_pair( "RIGHT", GLFW_KEY_RIGHT ) );
	key_binds.insert( std::make_pair( "HOME", GLFW_KEY_HOME ) );
	key_binds.insert( std::make_pair( "END", GLFW_KEY_END ) );
    key_binds.insert( std::make_pair( "KP_0", GLFW_KEY_KP_0 ) );
    key_binds.insert( std::make_pair( "KP_1", GLFW_KEY_KP_1 ) );
    key_binds.insert( std::make_pair( "KP_2", GLFW_KEY_KP_2 ) );
    key_binds.insert( std::make_pair( "KP_3", GLFW_KEY_KP_3 ) );
    key_binds.insert( std::make_pair( "KP_4", GLFW_KEY_KP_4 ) );
    key_binds.insert( std::make_pair( "KP_5", GLFW_KEY_KP_5 ) );
    key_binds.insert( std::make_pair( "KP_6", GLFW_KEY_KP_6 ) );
    key_binds.insert( std::make_pair( "KP_7", GLFW_KEY_KP_7 ) );
    key_binds.insert( std::make_pair( "KP_8", GLFW_KEY_KP_8 ) );
    key_binds.insert( std::make_pair( "KP_9", GLFW_KEY_KP_9 ) );
    key_binds.insert( std::make_pair( "A", GLFW_KEY_A ) );
    key_binds.insert( std::make_pair( "B", GLFW_KEY_B ) );
    key_binds.insert( std::make_pair( "C", GLFW_KEY_C ) );
    key_binds.insert( std::make_pair( "D", GLFW_KEY_D ) );
    key_binds.insert( std::make_pair( "E", GLFW_KEY_E ) );
    key_binds.insert( std::make_pair( "F", GLFW_KEY_F ) );
    key_binds.insert( std::make_pair( "G", GLFW_KEY_G ) );
    key_binds.insert( std::make_pair( "H", GLFW_KEY_H ) );
    key_binds.insert( std::make_pair( "I", GLFW_KEY_I ) );
    key_binds.insert( std::make_pair( "J", GLFW_KEY_J ) );
    key_binds.insert( std::make_pair( "K", GLFW_KEY_K ) );
    key_binds.insert( std::make_pair( "L", GLFW_KEY_L ) );
    key_binds.insert( std::make_pair( "M", GLFW_KEY_M ) );
    key_binds.insert( std::make_pair( "N", GLFW_KEY_N ) );
    key_binds.insert( std::make_pair( "O", GLFW_KEY_O ) );
    key_binds.insert( std::make_pair( "P", GLFW_KEY_P ) );
    key_binds.insert( std::make_pair( "Q", GLFW_KEY_Q ) );
    key_binds.insert( std::make_pair( "R", GLFW_KEY_R ) );
    key_binds.insert( std::make_pair( "S", GLFW_KEY_S ) );
    key_binds.insert( std::make_pair( "T", GLFW_KEY_T ) );
    key_binds.insert( std::make_pair( "U", GLFW_KEY_U ) );
    key_binds.insert( std::make_pair( "V", GLFW_KEY_V ) );
    key_binds.insert( std::make_pair( "W", GLFW_KEY_W ) );
    key_binds.insert( std::make_pair( "X", GLFW_KEY_X ) );
    key_binds.insert( std::make_pair( "Y", GLFW_KEY_Y ) );
    key_binds.insert( std::make_pair( "Z", GLFW_KEY_Z ) );
    key_binds.insert( std::make_pair( " ", GLFW_KEY_SPACE ) );
}

void Menu_Engine::createSettingsMenu()
{
    int half_screenWidth = this->screen_width / 2;
    int half_screenHeight = this->screen_height / 2;

    float scale = this->screen_height / 720;

    if ( this->screen_height / 360 == 3 )
        scale = 1.5 ;
    else
        scale = 1;

    std::cout << scale << std::endl;

    settings_menu.theme = new nanogui::Theme( base_screen->nvgContext() );
    settings_menu.theme->mButtonFontSize = 20 * scale;
    settings_menu.theme->mStandardFontSize = 30;
    settings_menu.theme->mFontBold = 0;
    settings_menu.theme->mTextColor = {230, 230, 230, 255};
    settings_menu.theme->mButtonCornerRadius = 5;
    settings_menu.theme->mBorderDark = {0, 0, 0, 0};
    settings_menu.theme->mBorderLight = {0, 0, 0, 0};
    settings_menu.theme->mBorderMedium = {0, 0, 0, 0};
    settings_menu.theme->mDropShadow = {0, 0, 0, 255};
    settings_menu.theme->mWindowCornerRadius = 5;
    settings_menu.theme->mWindowHeaderHeight = 40 * scale;

    settings_menu.settingsMenu_window = new nanogui::Window( base_screen, "Settings Menu" );
    settings_menu.settingsMenu_window->setPosition( { half_screenWidth - this->screen_width / 4 , half_screenHeight - this->screen_height / 4 } );
    settings_menu.settingsMenu_window->setSize( { half_screenWidth , half_screenHeight } );
    settings_menu.settingsMenu_window->setTheme( settings_menu.theme );

    //Resolution
    nanogui::Label *tmp_label = new nanogui::Label(settings_menu.settingsMenu_window, "Resolution:", "sans-bold", 30);
    tmp_label->setPosition( { 20 * scale, 50 * scale } );
    tmp_label->setSize( { 120 * scale, 20 * scale } );
    tmp_label->setColor({255, 255, 255, 255});

    settings_menu.res_720 = new nanogui::Button(settings_menu.settingsMenu_window, "1280 x 720");
    settings_menu.res_720->setFlags(nanogui::Button::ToggleButton);
    settings_menu.res_720->setPosition( { 20 * scale , 80 * scale } );
    settings_menu.res_720->setSize( { 95 * scale , 40 * scale} );
    settings_menu.res_720->setBackgroundColor( { 20, 100, 255, 100 } );
    settings_menu.res_720->setTheme( settings_menu.theme );
    settings_menu.res_720->setCallback([]{
        if ( settings_menu.res_type == 2 )
        {
            settings_menu.res_1080->setEnabled( true );
            settings_menu.res_720->setEnabled( false );
            settings_menu.res_type = 1;
            settings_menu.res_change = true;
        }
    });

    settings_menu.res_1080 = new nanogui::Button(settings_menu.settingsMenu_window, "1980 x 1080");
    settings_menu.res_1080->setFlags(nanogui::Button::ToggleButton);
    settings_menu.res_1080->setPosition( { 120 * scale , 80 * scale} );
    settings_menu.res_1080->setSize( {95 * scale, 40 * scale} );
    settings_menu.res_1080->setBackgroundColor( { 20, 100, 255, 100 } );
    settings_menu.res_1080->setTheme( settings_menu.theme );
    settings_menu.res_1080->setCallback([]{
        if ( settings_menu.res_type == 1 )
        {
            settings_menu.res_1080->setEnabled( false );
            settings_menu.res_720->setEnabled( true );
            settings_menu.res_type = 2;
            settings_menu.res_change = true;
        }
    });


    //Slider
    tmp_label = new nanogui::Label(settings_menu.settingsMenu_window, "Music Volume:", "sans-bold", 30);
    tmp_label->setPosition( { 20 * scale, 160 * scale } );
    tmp_label->setSize( { 155 * scale, 20 * scale } );
    tmp_label->setColor({255, 255, 255, 255});

    settings_menu.vol_slider = new nanogui::Slider(settings_menu.settingsMenu_window);
    settings_menu.vol_slider->setPosition( { 10 * scale, 185 * scale } );
    settings_menu.vol_slider->setSize( { 350 * scale, 30 * scale } );

    settings_menu.vol_slider->setRange( std::make_pair( 0.0f, 100.0f ) );
    settings_menu.vol_slider->setHighlightedRange( std::make_pair( 0.0f, 100.0f ) );

    settings_menu.vol_slider->setHighlightColor( { 245, 76, 282, 255} );

    settings_menu.vol_slider->setValue( 50.0f );

    nanogui::TextBox *textBox = new nanogui::TextBox( settings_menu.settingsMenu_window );
    textBox->setSize( { 120 * scale, 30 * scale} );
    textBox->setValue("50");
    textBox->setUnits("%");
    settings_menu.vol_slider->setCallback([textBox](float value) {
        textBox->setValue(std::to_string((int) ( value )));
    });
    settings_menu.vol_slider->setFinalCallback([&](float value) {
        engine->getConfig().setMusicVolume( value );
        std::cout << "Final slider value: " << (int) (value ) << std::endl;
    });
    textBox->setFontSize(20 * scale);
    textBox->setPosition( { 450 * scale, 185 * scale} );


    //Slider
    tmp_label = new nanogui::Label(settings_menu.settingsMenu_window, "SFX Volume:", "sans-bold", 30);
    tmp_label->setPosition( { 20 * scale, 230 * scale } );
    tmp_label->setSize( { 130 * scale, 20 * scale } );
    tmp_label->setColor({255, 255, 255, 255});

    settings_menu.sfx_volume = new nanogui::Slider(settings_menu.settingsMenu_window);
    settings_menu.sfx_volume->setPosition( { 10 * scale, 255 * scale } );
    settings_menu.sfx_volume->setSize( { 350 * scale, 30 * scale } );

    settings_menu.sfx_volume->setRange( std::make_pair( 0.0f, 100.0f ) );
    settings_menu.sfx_volume->setHighlightedRange( std::make_pair( 0.0f, 100.0f ) );

    settings_menu.sfx_volume->setHighlightColor( { 245, 76, 282, 255} );

    settings_menu.sfx_volume->setValue( 50.0f );

    nanogui::TextBox *textBox_2 = new nanogui::TextBox( settings_menu.settingsMenu_window );
    textBox_2->setSize( { 120 * scale, 30 * scale} );
    textBox_2->setValue("50");
    textBox_2->setUnits("%");
    settings_menu.sfx_volume->setCallback([textBox_2](float value) {
        textBox_2->setValue(std::to_string((int) ( value )));
    });
    settings_menu.sfx_volume->setFinalCallback([&](float value) {
        engine->getConfig().setSFXVolume( value );
        std::cout << "Final slider value: " << (int) (value ) << std::endl;
    });
    textBox_2->setFontSize(20 * scale);
    textBox_2->setPosition( { 450 * scale,255 * scale} );

    //Key Binds
    tmp_label = new nanogui::Label(settings_menu.settingsMenu_window, "Key Binds:", "sans-bold", 30);
    tmp_label->setPosition( { 450 * scale, 50 * scale } );
    tmp_label->setSize( { 110 * scale, 20 * scale } );
    tmp_label->setColor({255, 255, 255, 255});


    settings_menu.KeyBinds = new nanogui::PopupButton(settings_menu.settingsMenu_window, "Key Binds" );
    settings_menu.KeyBinds->setPosition( { 450 * scale, 85 * scale } );
    settings_menu.KeyBinds->setSize( { 130 * scale , 30 * scale } );
    settings_menu.KeyBinds->setBackgroundColor( { 20, 100, 255, 100 } );

    settings_menu.keybind_popup = settings_menu.KeyBinds->popup();
    settings_menu.keybind_popup->setSize( { 320 * scale, 270 * scale } );
    settings_menu.keybind_popup->setAnchorPos( { 550 * scale, 100 * scale } );

    std::cout << "LETS HP " << settings_menu.keybind_popup->anchorPos()[0] << " " << settings_menu.keybind_popup->anchorPos()[0] << std::endl;

    settings_menu.Button_Up = new nanogui::Button( settings_menu.keybind_popup, "Key_Up");
    settings_menu.Button_Up->setPosition( { 20 * scale, 20 * scale } );
    settings_menu.Button_Up->setSize( { 130 * scale, 30 * scale } );
    settings_menu.Button_Up->setBackgroundColor( { 20, 100, 255, 100 } );
    settings_menu.Button_Up->setTheme( settings_menu.theme );
    settings_menu.Button_Up->setCallback([]{

        bool tmp = true;

        if ( settings_menu.Button_Up->pushed() == true && settings_menu.Button_Down->enabled() == true)
        {
            tmp = !tmp;
            settings_menu.button_type = 1;
        }
        else
            settings_menu.button_type = 0;

        settings_menu.Button_Down->setEnabled( tmp );
        settings_menu.Button_Left->setEnabled( tmp );
        settings_menu.Button_Right->setEnabled( tmp );
        settings_menu.Button_Place->setEnabled( tmp );
    });

    settings_menu.Button_Down = new nanogui::Button(settings_menu.keybind_popup, "Key_Down");
    settings_menu.Button_Down->setPosition( { 170 * scale, 20 * scale } );
    settings_menu.Button_Down->setSize( { 130 * scale, 30 * scale } );
    settings_menu.Button_Down->setBackgroundColor( { 20, 100, 255, 100 } );
    settings_menu.Button_Down->setTheme( settings_menu.theme );
    settings_menu.Button_Down->setCallback([]{

            bool tmp = true;

            if ( settings_menu.Button_Down->pushed() == true && settings_menu.Button_Up->enabled() == true )
            {
                tmp = !tmp;
                settings_menu.button_type = 2;
            }
            else
                settings_menu.button_type = 0;

            settings_menu.Button_Up->setEnabled( tmp );
            settings_menu.Button_Left->setEnabled( tmp );
            settings_menu.Button_Right->setEnabled( tmp );
            settings_menu.Button_Place->setEnabled( tmp );
    });

    settings_menu.Button_Left = new nanogui::Button(settings_menu.keybind_popup, "Key_Left");
    settings_menu.Button_Left->setPosition( { 20 * scale, 60 * scale } );
    settings_menu.Button_Left->setSize( { 130 * scale, 30 * scale } );
    settings_menu.Button_Left->setBackgroundColor( { 20, 100, 255, 100 } );
    settings_menu.Button_Left->setTheme( settings_menu.theme );
    settings_menu.Button_Left->setCallback([]{

            bool tmp = true;

            if ( settings_menu.Button_Left->pushed() == true && settings_menu.Button_Up->enabled() == true )
            {
                tmp = !tmp;
                settings_menu.button_type = 3;
            }
            else
                settings_menu.button_type = 0;


            settings_menu.Button_Up->setEnabled( tmp );
            settings_menu.Button_Down->setEnabled( tmp );
            settings_menu.Button_Right->setEnabled( tmp );
            settings_menu.Button_Place->setEnabled( tmp );
    });

    settings_menu.Button_Right = new nanogui::Button(settings_menu.keybind_popup, "Key_Right");
    settings_menu.Button_Right->setPosition( { 170 * scale, 60 * scale } );
    settings_menu.Button_Right->setSize( { 130 * scale, 30 * scale } );
    settings_menu.Button_Right->setBackgroundColor( { 20, 100, 255, 100 } );
    settings_menu.Button_Right->setTheme( settings_menu.theme );
    settings_menu.Button_Right->setCallback([]{

            bool tmp = true;

            if ( settings_menu.Button_Right->pushed() == true && settings_menu.Button_Up->enabled() == true )
            {
                tmp = !tmp;
                settings_menu.button_type = 4;
            }
            else
                settings_menu.button_type = 0;


            settings_menu.Button_Down->setEnabled( tmp );
            settings_menu.Button_Left->setEnabled( tmp );
            settings_menu.Button_Up->setEnabled( tmp );
            settings_menu.Button_Place->setEnabled( tmp );
    });

    settings_menu.Button_Place = new nanogui::Button(settings_menu.keybind_popup, "Key_Place");
    settings_menu.Button_Place->setPosition( { 90 * scale, 100 * scale } );
    settings_menu.Button_Place->setSize( { 130 * scale, 30 * scale } );
    settings_menu.Button_Place->setBackgroundColor( { 20, 100, 255, 100 } );
    settings_menu.Button_Place->setTheme( settings_menu.theme );
    settings_menu.Button_Place->setCallback([]{

            bool tmp = true;

            if ( settings_menu.Button_Place->pushed() == true && settings_menu.Button_Up->enabled() == true )
            {
                tmp = !tmp;
                settings_menu.button_type = 5;
            }
            else
                settings_menu.button_type = 0;


            settings_menu.Button_Down->setEnabled( tmp );
            settings_menu.Button_Left->setEnabled( tmp );
            settings_menu.Button_Right->setEnabled( tmp );
            settings_menu.Button_Up->setEnabled( tmp );
    });

    settings_menu.key_textBox = new nanogui::TextBox( settings_menu.keybind_popup, "" );
    settings_menu.key_textBox->setPosition( { 50 * scale, 160 * scale } );
    settings_menu.key_textBox->setSize( { 210 * scale, 35 * scale } );
    settings_menu.key_textBox->setTheme( settings_menu.theme );
    settings_menu.key_textBox->setEditable( true );

    settings_menu.key_textBox->setCallback( []( const std::string& str )
    {
        for ( it = key_binds.begin(); it != key_binds.end(); it++)
        {
            if ( str.compare( it->first ) == 0 )
            {
                std::cout << it->first << " " << settings_menu.curr_up << std::endl;

                std::cout << it->second << std::endl;
                if ( settings_menu.curr_up == it->second || settings_menu.curr_down == it->second || settings_menu.curr_Left == it->second || settings_menu.curr_Right == it->second || settings_menu.curr_place == it->second)
                    break ;

                settings_menu.new_key = it->second;
                settings_menu.bind_change = true;
                settings_menu.Apply->setEnabled( true );

                return ( true );
            }
        }
        return ( false );
    });

    settings_menu.Apply = new nanogui::Button(settings_menu.keybind_popup, "Apply");
    settings_menu.Apply->setPosition( { 90 * scale, 215 * scale } );
    settings_menu.Apply->setSize( { 130 * scale, 30 * scale } );
    settings_menu.Apply->setBackgroundColor( { 20, 100, 255, 100 } );
    settings_menu.Apply->setTheme( settings_menu.theme );
    settings_menu.Apply->setCallback([]{

        if (settings_menu.bind_change && settings_menu.button_type != 0)
        {
            if (settings_menu.button_type == 1)
            {
                settings_menu.curr_up = settings_menu.new_key;
                engine->getConfig().setKBMoveUp( settings_menu.curr_up  );
            }
            else if (settings_menu.button_type == 2)
            {
                settings_menu.curr_down = settings_menu.new_key;
                engine->getConfig().setKBMoveDown( settings_menu.curr_down  );
            }
            else if (settings_menu.button_type == 3)
            {
                settings_menu.curr_Left = settings_menu.new_key;
                engine->getConfig().setKBMoveLeft( settings_menu.curr_Left  );
            }
            else if (settings_menu.button_type == 4)
            {
                settings_menu.curr_Right = settings_menu.new_key;
                engine->getConfig().setKBMoveRight( settings_menu.curr_Right );
            }
            else if (settings_menu.button_type == 5)
            {
                settings_menu.curr_place = settings_menu.new_key;
                engine->getConfig().setKBPlaceBomb( settings_menu.curr_place  );
            }

            settings_menu.Button_Down->setEnabled( true );
            settings_menu.Button_Left->setEnabled( true );
            settings_menu.Button_Right->setEnabled( true );
            settings_menu.Button_Up->setEnabled( true );
            settings_menu.Button_Place->setEnabled( true );
        }

        settings_menu.Apply->setEnabled( false );
    });

    settings_menu.Apply->setEnabled( false );

    settings_menu.back_button = new nanogui::Button(settings_menu.settingsMenu_window, "Return");
    settings_menu.back_button->setPosition( { half_screenWidth / 2 - half_screenWidth / 8 , 320 * scale } );
    settings_menu.back_button->setSize( { 170 * scale , 30 * scale} );
    settings_menu.back_button->setBackgroundColor( { 20, 100, 255, 100 } );
    settings_menu.back_button->setTheme( settings_menu.theme );
    settings_menu.back_button->setCallback([]{
        engine->getConfig().updateFile(engine->getPlayer(), engine->getMapLevel(), engine->getSound(), engine->getScore());
        settings_menu.changeView(false);
        if (engine->getGameState() != PAUSED)
            main_menu.changeView(true);
        else
            pause_menu.changeView(true);
    });
}

void Menu_Engine::createMainMenu()
{
    //nb: new button co-ords use windw dimension -> mainMenu_window;
    int half_screenWidth = this->screen_width / 2;
    int half_screenHeight = this->screen_height / 2;

    main_menu.theme = new nanogui::Theme( base_screen->nvgContext() );
    main_menu.theme->mButtonFontSize = 10 * ( this->screen_height / 360 );
    main_menu.theme->mFontBold = 0;
    main_menu.theme->mTextColor = {200, 200, 200, 255};
    main_menu.theme->mButtonCornerRadius = 5;
    main_menu.theme->mBorderDark = {20, 100, 150, 10};
    main_menu.theme->mBorderLight = {30, 150, 200, 10};
    main_menu.theme->mBorderMedium = {25, 150, 175, 10};
    main_menu.theme->mDropShadow = {20, 20, 20, 255};
    main_menu.theme->mWindowCornerRadius = 5;
    main_menu.theme->mWindowHeaderHeight = 20 * ( this->screen_height / 360 );

    main_menu.mainMenu_window = new nanogui::Window( base_screen, "Main Menu" );
    main_menu.mainMenu_window->setPosition( { half_screenWidth - this->screen_width / 4 , half_screenHeight - this->screen_height / 4 } );
    main_menu.mainMenu_window->setSize( { half_screenWidth , half_screenHeight } );
    main_menu.mainMenu_window->setTheme( main_menu.theme );

    /// dimensions and positions for buttons
    int     posY = half_screenHeight / 2 - half_screenHeight / 3;
    int     buttonHeight = 25 * ( this->screen_height / 360 );
    int     buttonWidth = half_screenWidth / 2;
    int     Xoffset = half_screenWidth / 4;
    int     posX = half_screenWidth / 2 - Xoffset;

    main_menu.load_game = new nanogui::Button(main_menu.mainMenu_window, "Continue");
    main_menu.load_game->setSize({buttonWidth, buttonHeight});
    main_menu.load_game->setBackgroundColor( { 20, 100, 255, 100 } );
    main_menu.load_game->setPosition({posX, posY});
    main_menu.load_game->setTheme(main_menu.theme);
    main_menu.load_game->setCursor(nanogui::Cursor::Hand);
    main_menu.load_game->setCallback([]{
        engine->setGameState(GAME);
        engine->getPlayer().setIsPaused(false);
        engine->setIsTransitioning(true);
        engine->transitionMap();
        main_menu.changeView(false);
        settings_menu.changeView(false);
        pause_menu.changeView(false);
    });

    posY += 35 * ( this->screen_height / 360 );
    main_menu.start = new nanogui::Button(main_menu.mainMenu_window, "New Game");
    main_menu.start->setSize( {buttonWidth, buttonHeight} );
    main_menu.start->setBackgroundColor( { 20, 100, 255, 100 } );
    main_menu.start->setPosition({posX, posY});
    main_menu.start->setTheme(main_menu.theme);
    main_menu.start->setCursor(nanogui::Cursor::Hand);
    main_menu.start->setCallback([]{
        engine->reset();
        engine->getPlayer().setIsPaused(false);
        main_menu.changeView(false);
        settings_menu.changeView(false);
        pause_menu.changeView(false);
    });

    posY += 35 * ( this->screen_height / 360 );
    main_menu.settings = new nanogui::Button(main_menu.mainMenu_window, "Settings");
    main_menu.settings->setSize({buttonWidth, buttonHeight});
    main_menu.settings->setBackgroundColor( { 20, 100, 255, 100 } );
    main_menu.settings->setPosition({posX, posY});
    main_menu.settings->setTheme(main_menu.theme);
    main_menu.settings->setCursor(nanogui::Cursor::Hand);
    main_menu.settings->setCallback([]{
        main_menu.changeView(false);
        settings_menu.changeView(true);
    });

    posY += 35 * ( this->screen_height / 360 );
    main_menu.exit_game = new nanogui::Button(main_menu.mainMenu_window, "EXIT");
    main_menu.exit_game->setSize({buttonWidth, buttonHeight});
    main_menu.exit_game->setBackgroundColor( { 20, 100, 255, 100 } );
    main_menu.exit_game->setPosition({posX, posY});
    main_menu.exit_game->setTheme(main_menu.theme);
    main_menu.exit_game->setCursor(nanogui::Cursor::Hand);
    main_menu.exit_game->setCallback([]{
        main_menu.changeView(false);
        exit(0);
    });
}

void Menu_Engine::gl_init()
{
    glfwMakeContextCurrent( base_screen->glfwWindow() ); // Make the windows context current
    // /glfwGetFramebufferSize( base_screen->glfwWindow(), &this->screen_width &this->Screen_Height );

    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    glViewport(0, 0, this->screen_width, this->screen_height);
    glfwSwapInterval(0);

    createMainMenu();
    createSettingsMenu();
    createPauseMenu();

    settings_menu.changeView(true);
    main_menu.changeView(false);
    pause_menu.changeView(false);
}

void Menu_Engine::createPauseMenu()
{
    int half_screenWidth = this->screen_width / 5;
    int half_screenHeight = this->screen_height / 3;

    pause_menu.pauseMenu_window = new nanogui::Window( base_screen, "Pause Menu" );
    pause_menu.pauseMenu_window->setPosition( { (this->screen_width / 2) - (half_screenWidth / 2) , (this->screen_height / 2) - (half_screenHeight / 2) } );
    pause_menu.pauseMenu_window->setSize( { half_screenWidth , half_screenHeight } );
    pause_menu.pauseMenu_window->setTheme( main_menu.theme );

    int     posY = (half_screenHeight / 2 - half_screenHeight / 3);
    int     buttonHeight = (20 * ( this->screen_height / 360 ));
    int     buttonWidth = (half_screenWidth / 2);
    int     Xoffset = half_screenWidth / 4;
    int     posX = (half_screenWidth / 2 - Xoffset);

    posY += 10 * (this->screen_height / 360);
    pause_menu.b_continue = new nanogui::Button(pause_menu.pauseMenu_window, "Continue");
    pause_menu.b_continue->setSize( {buttonWidth, buttonHeight} );
    pause_menu.b_continue->setBackgroundColor( { 20, 100, 255, 100 } );
    pause_menu.b_continue->setPosition({posX, posY});
    pause_menu.b_continue->setTheme(main_menu.theme);
    pause_menu.b_continue->setCursor(nanogui::Cursor::Hand);
    pause_menu.b_continue->setCallback([]{
        engine->setGameState(GAME);
        engine->getPlayer().setIsPaused(false);
        pause_menu.changeView(false);
        settings_menu.changeView(false);
    });

    posY += 30 * (this->screen_height / 360);
    pause_menu.b_settings = new nanogui::Button(pause_menu.pauseMenu_window, "Settings");
    pause_menu.b_settings->setSize( {buttonWidth, buttonHeight} );
    pause_menu.b_settings->setBackgroundColor( { 20, 100, 255, 100 } );
    pause_menu.b_settings->setPosition({posX, posY});
    pause_menu.b_settings->setTheme(main_menu.theme);
    pause_menu.b_settings->setCursor(nanogui::Cursor::Hand);
    pause_menu.b_settings->setCallback([]{
        pause_menu.changeView(false);
        settings_menu.changeView(true);
    });

    posY += 30 * (this->screen_height / 360);

    pause_menu.b_exit = new nanogui::Button(pause_menu.pauseMenu_window, "Main Menu");
    pause_menu.b_exit->setSize( {buttonWidth, buttonHeight} );
    pause_menu.b_exit->setBackgroundColor( { 20, 100, 255, 100 } );
    pause_menu.b_exit->setPosition({posX, posY});
    pause_menu.b_exit->setTheme(main_menu.theme);
    pause_menu.b_exit->setCursor(nanogui::Cursor::Hand);
    pause_menu.b_exit->setCallback([]{
        pause_menu.changeView(false);
        main_menu.changeView(true);
        settings_menu.changeView(false);
        engine->setGameState(MENU);
        engine->getConfig().setConfigUpdated(true);
    });
}

void Menu_Engine::init()
{
    if( !glfwInit() )
    {
        std::cout << "Bad news1" << std::endl; //Could Not Init GLFW: Failed?
        exit(1);
    }

    // open a window with GLFW, sets required GLFW options
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    base_screen = new nanogui::Screen( Eigen::Vector2i( this->screen_width, this->screen_height), "Bomberman", false, false, 8, 8, 24, 8, 4, 4, 1);
    base_screen->setBackground( { 0, 0, 0, 0 } );
    base_screen->setVisible(true);
    settings_menu.res_type = 1;

    if ( !base_screen->glfwWindow() ) // Check if window was created
    {
        std::cout << "Bad news2" << std::endl; //Could Not Create GLFW Window: Failed?
        glfwTerminate(); // Terminate GLFW
        exit(2);
    }

    std::cout << "Window Valei " << base_screen->glfwWindow() << std::endl;

    glfwMakeContextCurrent( base_screen->glfwWindow() ); // Make the windows context current
    // /glfwGetFramebufferSize( base_screen->glfwWindow(), &this->screen_width &this->Screen_Height );

    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    glViewport(0, 0, this->screen_width, this->screen_height);
    glfwSwapInterval(0);

    createMainMenu();
    createSettingsMenu();
    createPauseMenu();

    settings_menu.res_720->setEnabled( false );
    settings_menu.changeView(false);
    pause_menu.changeView(false);
    main_menu.changeView(true);
}

Menu_Engine::~Menu_Engine()
{
    return ;
}

GLFWwindow *Menu_Engine::GetWindow() const
{
    return ( base_screen->glfwWindow() );
}

bool Menu_Engine::check_status()
{
    if ( main_menu.mainMenu_window->visible() == true || settings_menu.settingsMenu_window->visible() == true )
        return ( true );
    return ( false );
}

int Menu_Engine::update( Engine &engine )
{
    int change_val = 0;

    if ( base_screen->visible() == false )
        base_screen->setVisible(true);

    if (engine.getGameState() == MENU && engine.getConfig().getMapLevel() > 0)
        main_menu.load_game->setEnabled(true);
    else if (engine.getGameState() == MENU && engine.getConfig().getMapLevel() == 0 )
        main_menu.load_game->setEnabled(false);

    if (engine.getGameState() == PAUSED && !settings_menu.settingsMenu_window->visible() && !main_menu.mainMenu_window->visible() && !pause_menu.pauseMenu_window->visible())
    {
        pause_menu.changeView(true);
    }
    else if (engine.getGameState() == MENU && !settings_menu.settingsMenu_window->visible() && !main_menu.mainMenu_window->visible() && !pause_menu.pauseMenu_window->visible())
    {
        main_menu.changeView(true);
    }

    if ( settings_menu.res_change == true )
    {
        change_val = 1;
        int tmp = settings_menu.res_type;
        if ( settings_menu.res_type == 1 )
        {
            this->screen_width = 1280;
            this->screen_height = 720;
        }
        else if ( settings_menu.res_type ==  2)
        {
            this->screen_width = 1980;
            this->screen_height = 1080;
        }

        delete base_screen;

        base_screen = new nanogui::Screen( Eigen::Vector2i( this->screen_width, this->screen_height ), "Bomberman", false, false, 8, 8, 24, 8, 4, 4, 1);

        if ( !base_screen->glfwWindow() ) // Check if window was created
        {
            std::cout << "Bad news2" << std::endl; //Could Not Create GLFW Window: Failed?
            glfwTerminate(); // Terminate GLFW
            exit(2);
        }

        gl_init();

        settings_menu.res_change = false;
        settings_menu.res_type = tmp;

        if ( settings_menu.res_type == 1)
            settings_menu.res_720->setEnabled( false );
        else
            settings_menu.res_1080->setEnabled( false );
    }



    if ( main_menu.mainMenu_window->visible() == true || settings_menu.settingsMenu_window->visible() == true || pause_menu.pauseMenu_window->visible() == true)
        base_screen->drawAll();

    return (change_val);
}
