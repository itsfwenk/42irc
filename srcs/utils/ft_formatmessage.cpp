#include "Channel.hpp"
#include "Client.hpp"
#include "utils.hpp"

std::string ft_formatmessage(std::string code, std::string message, Client* client) {
    return code + " " + client->getNickname() + " :" + message;
};

std::string ft_formatmessage(std::string code, std::string message, Client* client, Channel* channel) {
    if (!channel)
        return ft_formatmessage(code, message, client);
    return code + " " + client->getNickname() + " #" + channel->getName() + " :" + message;
};