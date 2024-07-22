SRCS = srcs/main.cpp srcs/server/Cluster.cpp srcs/config/ConfigManager.cpp srcs/config/Config.cpp srcs/config/ServerParser.cpp srcs/utils/Utils.cpp
OBJ_DIR = obj
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

NAME = webserv

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address
INCLUDES = -Isrcs -Isrcs/config -Isrcs/utils -Isrcs/server

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
