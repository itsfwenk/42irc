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

// JOIN
# define ERR_BADCHANMASK(channelName) HOST "476 " + channelName + " :Bad Channel Mask"
# define RPL_JOIN(fullUserId, channelName) fullUserId + " JOIN :#" + channelName
# define RPL_TOPIC(clientNickname, channelName, channelTopic) HOST "332 " + clientNickname + " #" + channelName + " " + channelTopic
# define RPL_NAMREPLY(clientNickname, channelName, nicknamesList) HOST "353 " + clientNickname + " = #" + channelName + " :" + nicknamesList
# define RPL_ENDOFNAMES(clientNickname, channelName) HOST "366 " + clientNickname + " #" + channelName + " :End of /NAMES list"
# define ERR_BADCHANNELKEY(clientNickname, channelName) HOST "476 " + clientNickname + " #" + channelName + " :Cannot join channel (+k)"
# define ERR_CHANNELISFULL(clientNickname, channelName) HOST "471 " + clientNickname + " #" + channelName + " :Cannot join channel (+l)"
# define ERR_INVITEONLYCHAN(clientNickname, channelName) HOST "473 " + clientNickname + " #" + channelName + " :Cannot join channel (+i)"

// NICK
# define ERR_NONICKNAMEGIVEN(clientNickname) HOST "431 " + clientNickname + " :No nickname given"
# define ERR_ERRONEUSNICKNAME(oldNickname, newNickname) HOST "432 " + oldNickname + " " + newNickname + " :Erroneus nickname"
# define ERR_NICKNAMEINUSE(oldNickname, newNickname) HOST "433 " + oldNickname + " " + newNickname + " :Nickname is already in use"
# define RPL_NICK(fullUserId, newNickname) fullUserId + " NICK " + newNickname

// PART
# define RPL_PART(fullUserId, channelName, reason) fullUserId + " PART #" + channelName + " :" + reason

// PASS
# define ERR_PASSWDMISMATCH(clientNickname) HOST "464 " + clientNickname + " :Password incorrect"

// PRIVMSG
# define ERR_NOTEXTTOSEND(clientNickname) HOST "412 " + clientNickname + " :No text to send"
# define ERR_NORECIPIENT(clientNickname) HOST "411 " + clientNickname + " :No recipient given PRIVMSG"
# define ERR_NOSUCHNICK(clientNickname, destination) HOST "401 " + clientNickname + " " + destination + " :No such nick/channel"
# define ERR_NOTONCHANNEL(clientNickname, channelName) HOST "442 " + clientNickname + " #" + channelName + " :You're not on that channel"
# define RPL_PRIVMSG(fullUserId, destination, message) fullUserId + " PRIVMSG " + destination + " " + message

// PING
# define RPL_PONG(fullUserId, token) fullUserId + " PONG :" + token

// QUIT
# define RPL_QUIT(fullUserId, reason) fullUserId + " QUIT :" + reason

#endif

// From https://modern.ircdocs.horse/