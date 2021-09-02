CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98
RM = rm -f
NAME = ft_containers
SRC=
OBJ=

all: $(NAME)

$(NAME): $(CXX) $(CXXFLAGS) $(OBJ)

clean:

fclean:

re:

.PHONY: all clean $(NAME) fclean re
