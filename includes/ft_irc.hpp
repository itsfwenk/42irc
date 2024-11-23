#pragma once
#ifndef FT_IRC_HPP
# define FT_IRC_HPP

// Includes
# include <string>
# include <cstring>
# include <ctime>
# include <stdlib.h>
# include <vector>
# include <map>
# include <stack>
# include <algorithm>
# include <iostream>
# include <sstream>
# include <poll.h>
# include <ifaddrs.h>
# include <arpa/inet.h>
# include <signal.h>

// Server
# include "Server.hpp"

// Commands
# include "CAP.hpp"
# include "NICK.hpp"
# include "PASS.hpp"
# include "PING.hpp"
# include "QUIT.hpp"
# include "USER.hpp"

// Utils
# include "replies.hpp"

// print_utils.cpp
std::string getFormattedTime(time_t _time);
std::string getStringFromNumber(int number);
void 		print_logo(void);
void 		print_colored(std::string message, std::string color);
void		print_success(std::string success);
void		print_info(std::string info);
void 		print_warning(std::string warning);
void 		print_error(std::string error);

// Colors
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PURPLE "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[0m"
# define END_COLOR "\e[0m"
# define BOLD "\e[1m"

// Defines
# define DEFAULT_NAME ""
# define CRLF "\r\n"
# define MESSAGE_SIZE 1024
# define CHANNEL_NAME_MAX_LEN 200
# define AUTO_LOGOUT_TIMEOUT 42
# define TOPIC_MAX_LEN 307
# define HOST ":localhost "

// Structs
struct execReturnData {
    std::string message;
    std::vector<int> clientsFds;
};

struct IRCMessage {
    std::string prefix;
    std::string command;
    std::vector<std::string> params;
    std::string text;
};

#endif
