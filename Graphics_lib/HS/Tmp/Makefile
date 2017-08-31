CLANG =	clang++

NAME = Render

CFLAGS =

C++_TYPE = -std=c++11 -g -o3

TEXTURE = -L. libsoil2-debug.a

HEADER = ./Inc/

SRC_PATH = ./Src/

SRC = $(SRC_PATH)main.cpp $(SRC_PATH)Render_Engine.cpp $(SRC_PATH)Model.cpp $(SRC_PATH)Render.cpp $(SRC_PATH)Data_Loader.cpp $(SRC_PATH)Shaders.cpp $(SRC_PATH)Camera.cpp $(SRC_PATH)Text_Model.cpp $(SRC_PATH)Model_Text.cpp $(SRC_PATH)Object_Loader.cpp
OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CLANG) -c $(CFLAGS) $(C++_TYPE) $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CLANG) $(CFLAGS) $(C++_TYPE) -Qunused-arguments -lGL -lGLU -lGLEW -lglut -lglfw -o $(NAME) $(OBJ) $(TEXTURE)

clean:
	find . -type f | xargs touch
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
