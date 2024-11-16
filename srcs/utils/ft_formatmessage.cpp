#include "Channel.hpp"
#include "Client.hpp"
#include "utils.hpp"

std::string ft_formatmessage(std::string code, std::string message, Client* client) {
    return code + " " + client->getNickname() + " :" + message;
};

std::string ft_formatmessage(std::string code, std::string message, Client* client, Channel* channel) {
    return code + " " + client->getNickname() + " #" + channel->getName() + " :" + message;
};