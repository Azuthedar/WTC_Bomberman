#include "../include/Menu_Engine.hpp"

nanogui::Screen *Menu_Engine::base_screen = nullptr;
MainMenu Menu_Engine::main_menu = MainMenu();
SettingsMenu Menu_Engine::settings_menu = SettingsMenu();

Menu_Engine::Menu_Engine( std::string Win_Name )
{
    this->window_name = Win_Name;
    this->screen_width = 1280;
    this->screen_height = 720;

    init();
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
    tmp_label = new nanogui::Label(settings_menu.settingsMenu_window, "Volume:", "sans-bold", 30);
    tmp_label->setPosition( { 20 * scale, 140 * scale } );
    tmp_label->setSize( { 120 * scale, 20 * scale } );
    tmp_label->setColor({255, 255, 255, 255});

    settings_menu.vol_slider = new nanogui::Slider(settings_menu.settingsMenu_window);
    settings_menu.vol_slider->setPosition( { 10 * scale, 165 * scale } );
    settings_menu.vol_slider->setSize( { 350 * scale, 30 * scale } );

    std::pair<float, float> range( 0.0f, 100.0f);
    settings_menu.vol_slider->setRange( range );

    std::pair<float, float> highlightedRange( 0.0f, 100.0f );
    settings_menu.vol_slider->setHighlightedRange( highlightedRange );

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
        std::cout << "Final slider value: " << (int) (value ) << std::endl;
    });
    textBox->setFontSize(20 * scale);
    textBox->setPosition( { 450 * scale,165 * scale} );


    //Key Binds
    tmp_label = new nanogui::Label(settings_menu.settingsMenu_window, "Key Binds:", "sans-bold", 30);
    tmp_label->setPosition( { 20 * scale, 210 * scale } );
    tmp_label->setSize( { 110 * scale, 20 * scale } );
    tmp_label->setColor({255, 255, 255, 255});


    settings_menu.KeyBinds = new nanogui::PopupButton(settings_menu.settingsMenu_window, "Key Binds" );
    settings_menu.KeyBinds->setPosition( { 20 * scale, 240 * scale } );
    settings_menu.KeyBinds->setSize( { 130 * scale , 30 * scale } );

    settings_menu.keybind_popup = settings_menu.KeyBinds->popup();
    settings_menu.keybind_popup ->setLayout(new nanogui::GroupLayout());

    nanogui::CheckBox *tmp_Checkbox = new nanogui::CheckBox(settings_menu.keybind_popup, "Key_Up");
    tmp_Checkbox = new nanogui::CheckBox(settings_menu.keybind_popup, "Key_Down");
    tmp_Checkbox = new nanogui::CheckBox(settings_menu.keybind_popup, "Key_Left");
    tmp_Checkbox = new nanogui::CheckBox(settings_menu.keybind_popup, "Key_Right");
    tmp_Checkbox = new nanogui::CheckBox(settings_menu.keybind_popup, "Key_Place");

    nanogui::TextBox *key_textBox = new nanogui::TextBox( settings_menu.keybind_popup );
    key_textBox->setEditable( true );

    settings_menu.keybind_popup->performLayout( base_screen->nvgContext() );


    settings_menu.back_button = new nanogui::Button(settings_menu.settingsMenu_window, "Return");
    settings_menu.back_button->setPosition( { half_screenWidth / 2 - half_screenWidth / 8 , 320 * scale } );
    settings_menu.back_button->setSize( { 170 * scale , 30 * scale} );
    settings_menu.back_button->setTheme( settings_menu.theme );
    settings_menu.back_button->setCallback([]{
        settings_menu.changeView(false);
        main_menu.changeView(true);
    });


    /*new nanogui::Label(settings_menu.settingsMenu_window, "Popup buttons", "sans-bold");
    nanogui::PopupButton *popupBtn = new nanogui::PopupButton(settings_menu.settingsMenu_window, "Popup", ENTYPO_ICON_EXPORT);
    nanogui::Popup *popup = popupBtn->popup();
    popup->setLayout(new nanogui::GroupLayout());
    new nanogui::Label(popup, "Arbitrary widgets can be placed here");
    new nanogui::CheckBox(popup, "A check box");
    popupBtn = new nanogui::PopupButton(popup, "Recursive popup", ENTYPO_ICON_FLASH);
    popup = popupBtn->popup();
    popup->setLayout(new nanogui::GroupLayout());
    new nanogui::CheckBox(popup, "Another check box");*/

    /// dimensions and positions for buttons
}

void Menu_Engine::createMainMenu()
{
    //nb: new button co-ords use windw dimension -> mainMenu_window;
    int half_screenWidth = this->screen_width / 2;
    int half_screenHeight = this->screen_height / 2;

    main_menu.theme = new nanogui::Theme( base_screen->nvgContext() );
    main_menu.theme->mButtonFontSize = 10 * ( this->screen_height / 360 );
    main_menu.theme->mFontBold = 0;
    main_menu.theme->mTextColor = {230, 230, 230, 255};
    main_menu.theme->mButtonCornerRadius = 5;
    main_menu.theme->mBorderDark = {0, 0, 0, 0};
    main_menu.theme->mBorderLight = {0, 0, 0, 0};
    main_menu.theme->mBorderMedium = {0, 0, 0, 0};
    main_menu.theme->mDropShadow = {0, 0, 0, 255};
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

    main_menu.start = new nanogui::Button(main_menu.mainMenu_window, "New Game");
    main_menu.start->setSize( {buttonWidth, buttonHeight} );
    main_menu.start->setBackgroundColor( { 0, 0, 225, 255 } );
    main_menu.start->setPosition({posX, posY});
    main_menu.start->setTheme(main_menu.theme);
    main_menu.start->setCursor(nanogui::Cursor::Hand);
    main_menu.start->setCallback([]{
        main_menu.changeView(false);
        settings_menu.changeView(false);
        //glfwSetInputMode( base_screen->glfwWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    });

    posY += 35 * ( this->screen_height / 360 );
    main_menu.load_game = new nanogui::Button(main_menu.mainMenu_window, "Load Game");
    main_menu.load_game->setSize({buttonWidth, buttonHeight});
    main_menu.load_game->setBackgroundColor( { 255, 198, 0, 255 } );
    main_menu.load_game->setPosition({posX, posY});
    main_menu.load_game->setTheme(main_menu.theme);
    main_menu.load_game->setCursor(nanogui::Cursor::Hand);

    posY += 35 * ( this->screen_height / 360 );
    main_menu.settings = new nanogui::Button(main_menu.mainMenu_window, "Settings");
    main_menu.settings->setSize({buttonWidth, buttonHeight});
    main_menu.settings->setBackgroundColor( { 0, 225, 0, 255 } );
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
    main_menu.exit_game->setBackgroundColor( { 225, 0, 0, 255 } );
    main_menu.exit_game->setPosition({posX, posY});
    main_menu.exit_game->setTheme(main_menu.theme);
    main_menu.exit_game->setCursor(nanogui::Cursor::Hand);
    main_menu.exit_game->setCallback([]{
        main_menu.changeView(false);
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

    settings_menu.changeView(true);
    main_menu.changeView(false);
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

    base_screen = new nanogui::Screen( Eigen::Vector2i( this->screen_width, this->screen_height ), "Bomberman", true, false, 8, 8, 24, 8, 4, 4, 1);
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

    settings_menu.res_720->setEnabled( false );
    settings_menu.changeView(false);
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

int Menu_Engine::update()
{
    int change_val = 0;

    if ( base_screen->visible() == false )
        base_screen->setVisible(true);

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

        base_screen = new nanogui::Screen( Eigen::Vector2i( this->screen_width, this->screen_height ), "Bomberman", true, false, 8, 8, 24, 8, 4, 4, 1);

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

    if ( main_menu.mainMenu_window->visible() == true || settings_menu.settingsMenu_window->visible() == true )
        base_screen->drawAll();

    return (change_val);
}
