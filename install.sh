echo "Installing CMake..."
brew install cmake
echo "Installing Assimp..."
brew install assimp
echo "Installing GLFW..."
brew install glfw
echo "Installing Glew..."
brew install glew
echo "Installing FreeAlut..."
brew install freealut
echo "Installing GLM..."
brew install glm
echo "Installing SDL2..."
brew install sdl2
echo "Installing SDL2_MIXER..."
brew install sdl2_mixer
echo "Installing Python 3"
brew install python3
echo "Extracting NanoGUI"
unzip ./Libs/nanogui.zip -d ./Libs
#echo "Retrieving Assets"
#git clone https://github.com/NodziGames/Bomberman_Assets.git BA
#mv -f BA/Assets .
#mv -f BA/Libs .
#rm -rf BA
cmake .
make
