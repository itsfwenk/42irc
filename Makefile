NAME 			= ircserv
CC				= c++

CLASSES_SRCS	= Channel.cpp Client.cpp Command.cpp Server.cpp
COMMANDS_SRCS	= BOT.cpp CAP.cpp INVITE.cpp  JOIN.cpp KICK.cpp MODE.cpp NICK.cpp PASS.cpp PING.cpp PRIVMSG.cpp QUIT.cpp TOPIC.cpp USER.cpp WHOIS.cpp
UTILS_SRCS		= ft_convert.cpp ft_formatmessage.cpp ft_print.cpp ft_setsockopts.cpp RPN.cpp
MAIN_SRCS		= ft_irc.cpp

SOURCES			= $(addprefix srcs/classes/, $(CLASSES_SRCS)) \
				  $(addprefix srcs/commands/, $(COMMANDS_SRCS)) \
				  $(addprefix srcs/utils/, $(UTILS_SRCS)) \
 				  $(addprefix srcs/, $(MAIN_SRCS))
OBJECTS			= $(SOURCES:.cpp=.o)
OBJECTS_FOLDER  = $(addprefix objs/, $(OBJECTS))

HEADERS_FILES	= Channel.hpp Client.hpp Command.hpp RPN.hpp Server.hpp utils.hpp
CMD_HEADERS		= BOT.hpp CAP.hpp INVITE.hpp  JOIN.hpp KICK.hpp MODE.hpp NICK.hpp PASS.hpp PING.hpp PRIVMSG.hpp QUIT.hpp TOPIC.hpp USER.hpp  WHOIS.hpp

HEADERS			= $(addprefix includes/commands/, $(CMD_HEADERS)) \
				  $(addprefix includes/, $(HEADERS_FILES))

FLAGS 			= -Wall -Wextra -Werror -g3 -std=c++98
OPTIONS 		= -I includes -I includes/commands

#################################################################################

RED 	 = '\033[0;31m'
GREEN 	 = '\033[0;32m'
YELLOW 	 = '\033[0;33m'
BLUE 	 = '\033[0;34m'
PURPLE 	 = '\033[0;35m'
NC 		 = '\033[0m'

#################################################################################

objs/%.o: %.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $(OPTIONS) $< -o $@
	@echo $(GREEN)✅ $< compiled! $(NC)

$(NAME): $(OBJECTS_FOLDER) $(HEADERS)
	@$(CC) $(FLAGS) $(OPTIONS) -o $@ $(OBJECTS_FOLDER)
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
