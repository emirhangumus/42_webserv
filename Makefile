SRCS = srcs/main.cpp srcs/config/Config.cpp srcs/utils/Utils.cpp
OBJ_DIR = obj
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

NAME = webserv

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g
INCLUDES = -Isrcs -Isrcs/config -Isrcs/utils

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
