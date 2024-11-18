#include "USER.hpp"

USER::USER(void): Command("USER", 1, false, false, false) {};
USER::~USER(void) {};

void USER::run(Client* client, Channel* channel, std::vector<std::string> params) {
	std::string username = params[0];
	client->setUsername(username);
	return client->sendMessage(ft_formatmessage(RPL_WELCOME, client->getNickname() + "'s username edited successfully to: " + username, client, channel), channel);
};
