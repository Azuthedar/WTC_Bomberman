CLANG = clang++

NAME = BomberMan

CFLAGS =

C++_TYPE = -std=c++11 -g -o3

INCLUDE_PATHS = -I ~/.brew/Cellar/glfw/3.2.1/include -I ~/.brew/Cellar/glew/2.1.0/include/ -I ~/.brew/include -I include/

LIBRARY_PATHS = -L ~/.brew/Cellar/glfw/3.2.1/lib/ -L ~/.brew/Cellar/glew/2.1.0/lib/

LINKER_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo -framework Carbon -lglfw -lGLEW

TEXTURE = -L. libsoil2-debug.a

HEADER = ./Graphics_lib/Inc/
HEADER_TWO = ./include/

SRC_PATH = ./Graphics_lib/Src/
SRC_TWO = ./src/

SRC = $(SRC_TWO)Bomb.class.cpp $(SRC_TWO)Player.class.cpp $(SRC_TWO)Wall.class.cpp $(SRC_TWO)AEntity.class.cpp $(SRC_TWO)Gate.class.cpp $(SRC_TWO)Exception.class.cpp $(SRC_TWO)Powerup.class.cpp $(SRC_TWO)Enemy.class.cpp $(SRC_TWO)Explosion.class.cpp $(SRC_TWO)GameEngine.class.cpp $(SRC_TWO)main.cpp $(SRC_PATH)Render_Engine.cpp $(SRC_PATH)Model.cpp $(SRC_PATH)Component.cpp $(SRC_PATH)Render.cpp $(SRC_PATH)Data_Loader.cpp $(SRC_PATH)Shaders.cpp $(SRC_PATH)Camera.cpp $(SRC_PATH)Text_Model.cpp $(SRC_PATH)Light_class.cpp $(SRC_PATH)Model_Text.cpp $(SRC_PATH)Object_Loader.cpp

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CLANG) -c $(INCLUDE_PATHS) $(C++_TYPE) $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CLANG) $(CFLAGS) $(C++_TYPE) -Qunused-arguments -lGL -lGLU -lGLEW -lglut -lglfw -o $(NAME) $(OBJ) $(TEXTURE)

mac: $(OBJ) $(HEADER_TWO) $(HEADER)
	$(CLANG) $(C++_TYPE) $(INCLUDE_PATHS) $(LINKER_FLAGS) -o $(NAME) $(OBJ) $(TEXTURE) $(LIBRARY_PATHS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
