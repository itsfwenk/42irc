NAME 			= ircserv
CC				= c++

CLASSES_SRCS	= Channel.cpp Client.cpp Server.cpp
UTILS_SRCS		= ft_convert.cpp ft_print.cpp ft_setsockopts.cpp
MAIN_SRCS		= ft_irc.cpp

SOURCES			= $(addprefix srcs/classes/, $(CLASSES_SRCS)) \
				  $(addprefix srcs/utils/, $(UTILS_SRCS)) \
 				  $(addprefix srcs/, $(MAIN_SRCS))
OBJECTS			= $(SOURCES:.cpp=.o)

HEADERS_FILES	= Channel.hpp Client.hpp Server.hpp utils.hpp
HEADERS			= $(addprefix includes/, $(HEADERS_FILES))

FLAGS 			= -Wall -Wextra -Werror -g3 -std=c++98
OPTIONS 		= -I includes

#################################################################################

RED 	 = '\033[0;31m'
GREEN 	 = '\033[0;32m'
YELLOW 	 = '\033[0;33m'
BLUE 	 = '\033[0;34m'
PURPLE 	 = '\033[0;35m'
NC 		 = '\033[0m'

#################################################################################

%.o: %.cpp $(HEADERS)
	@mkdir -p $(dir objs/$@)
	@$(CC) $(FLAGS) -c $(OPTIONS) $< -o objs/$@
	@echo $(GREEN)✅ $< compiled! $(NC)

$(NAME): $(OBJECTS) $(HEADERS)
	@$(CC) $(FLAGS) $(OPTIONS) -o $@ $(addprefix objs/, $(OBJECTS))
	@echo $(BLUE)✅ $@ built! $(NC)

all: $(NAME)

clean:
	@rm -rf objs
	@echo $(YELLOW)🗑️ objs directory deleted! $(NC)

fclean: clean
	@rm -f $(NAME)
	@echo $(RED)🗑️ $(NAME) deleted! $(NC)

re: fclean all

.PHONY: all clean fclean re
