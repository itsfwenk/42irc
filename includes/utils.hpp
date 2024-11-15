#pragma once
#ifndef UTILS_HPP
# define UTILS_HPP

# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PURPLE "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[0m"
# define END_COLOR "\e[0m"
# define BOLD "\e[1m"

# include <iostream>
# include <string>
# include <stdlib.h>
# include <ifaddrs.h>
# include <arpa/inet.h>
# include <poll.h>

// ft_convert.cpp
int ft_get_converted_port(std::string port);

// ft_print.cpp
void ft_print_logo(void);
void ft_print_message(std::string msg, std::string color);
void ft_print_success(std::string success);
void ft_print_info(std::string info);
void ft_print_warning(std::string warning);
void ft_print_error(std::string error);

// ft_setsockopts.cpp
void ft_setsockopts(int sockfd);

#endif
