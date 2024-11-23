#pragma once
#ifndef REPLIES_HPP
# define REPLIES_HPP

# include "ft_irc.hpp"

// Utils
# define ERR_UNKNOWNCOMMAND(clientNickname, commandName) HOST "421 " + clientNickname + " " + commandName + " :Unknown command"
# define ERR_NEEDMOREPARAMS(clientNickname, commandName) HOST "461 " + clientNickname + " " + commandName + " :Not enough parameters"
# define ERR_ALREADYREGISTERED(clientNickname) HOST "462 " + clientNickname + " :You may not reregister"

// RPL
# define RPL_WELCOME(fullUserId, clientNickname) HOST "001 " + clientNickname + " :Welcome to the 42 ft_irc " + fullUserId
# define RPL_YOURHOST(clientNickname) HOST "002 " + clientNickname + " :Your host is ft_irc 1.0"
# define RPL_CREATED(clientNickname, dateTime) HOST "003 " + clientNickname + " :Created at " + dateTime
# define RPL_ISUPPORT(clientNickname) HOST "005 " + clientNickname + " NICKLEN=9 CHANNELLEN=200 TOPICLEN=307"

// NICK
# define ERR_NONICKNAMEGIVEN(clientNickname) HOST "431 " + clientNickname + " :No nickname given"
# define ERR_ERRONEUSNICKNAME(oldNickname, newNickname) HOST "432 " + oldNickname + " " + newNickname + " :Erroneus nickname"
# define ERR_NICKNAMEINUSE(oldNickname, newNickname) HOST "433 " + oldNickname + " " + newNickname + " :Nickname is already in use"
# define RPL_NICK(fullUserId, newNickname) fullUserId + " NICK " + newNickname

// PASS
# define ERR_PASSWDMISMATCH(clientNickname) HOST "464 " + clientNickname + " :Password incorrect"

// PING
# define RPL_PONG(fullUserId, token) fullUserId + " PONG :" + token

// QUIT
# define RPL_QUIT(fullUserId, reason) fullUserId + " QUIT :" + reason

#endif

// From https://modern.ircdocs.horse/