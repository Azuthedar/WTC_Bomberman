NAME = Atjarman

SRC = src/*.cpp

OBJ = *.o

C_FLAGS = -Wall -Werror -Wextra -g3

INCL = include/

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

all: $(NAME)


$(NAME):
	@echo "$(COM_COLOR)Compiling OBJECT files $(NAME) $(NO_COLOR)"
	@g++ $(C_FLAGS) -c $(SRC) -I $(INCL)
	@echo "$(COM_COLOR)Compiling executable $(NAME)$(NO_COLOR)"
	@g++ $(C_FLAGS) -o $(NAME) $(OBJ)

clean:
	@echo "$(WARN_COLOR)Deleting all OBJ files$(NO_COLOR)"
	@rm -rf $(OBJ)


fclean: clean
	@echo "$(WARN_COLOR)Deleting executable $(NAME)$(NO_COLOR)"
	@rm -rf $(NAME)

re: fclean all
