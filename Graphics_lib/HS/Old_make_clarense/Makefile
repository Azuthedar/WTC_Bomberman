# OBJS specifies which files to compile as part of the project
OBJS = src/*.cpp

# CC specifies which compiler we're using
CC = g++

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I ~/.brew/Cellar/sfml/2.4.2/include -I include/

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L ~/.brew/Cellar/sfml/2.4.2/lib -lsfml-graphics -lsfml-window -lsfml-system

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall -Werror -Wextra

# LINKER_FLAGS specifies the libraries we're linking against
# Cocoa, IOKit, and CoreVideo are needed for static GLFW3.
LINKER_FLAGS = 

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = AtjarMan

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	@echo "Please run the following command: export LD_LIBRARY_PATH=~/.brew/lib && ./$(OBJ_NAME)"

clean :
	rm -rf $(OBJ_NAME)

re: clean all
