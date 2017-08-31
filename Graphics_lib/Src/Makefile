CLANG =	clang++

NAME = Game

CFLAGS =

C++_TYPE = -std=c++11 -g -o3

TEXTURE = -L. libsoil2-debug.a

HEADER = ./Graphics_lib/Inc/
HEADER_TWO = ./include/

SRC_PATH = ./Graphics_lib/Src/
SRC_TWO = ./src/

SRC = $(SRC_PATH)Render_Engine.cpp $(SRC_PATH)Model.cpp $(SRC_PATH)Component.cpp $(SRC_PATH)Render.cpp $(SRC_PATH)Data_Loader.cpp $(SRC_PATH)Shaders.cpp $(SRC_PATH)Camera.cpp $(SRC_PATH)Text_Model.cpp $(SRC_PATH)Light_class.cpp $(SRC_PATH)Model_Text.cpp $(SRC_PATH)Object_Loader.cpp $(SRC_TWO)Player.class.cpp $(SRC_TWO)Bomb.class.cpp $(SRC_TWO)Wall.class.cpp $(SRC_TWO)AEntity.class.cpp $(SRC_TWO)Gate.class.cpp $(SRC_TWO)Exception.class.cpp $(SRC_TWO)Powerup.class.cpp $(SRC_TWO)Enemy.class.cpp $(SRC_TWO)Explosion.class.cpp $(SRC_TWO)GameEngine.class.cpp $(SRC_TWO)main.cpp 

OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CLANG) -c $(CFLAGS) $(C++_TYPE) $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER_TWO) $(HEADER)
	$(CLANG) $(CFLAGS) $(C++_TYPE) -Qunused-arguments -lGL -lGLU -lGLEW -lglut -lglfw -o $(NAME) $(OBJ) $(TEXTURE)

clean:
	find . -type f | xargs touch
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
