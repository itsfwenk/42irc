#include "PASS.hpp"

PASS::PASS(void): Command("PASS", 1, false, false, false) {};
PASS::~PASS(void) {};

void PASS::run(Client* client, Channel* channel, std::vector<std::string> params) {
	if (client->isLoggedIn())
		return client->sendMessage(ft_formatmessage(ERR_ALREADYREGISTERED, "You are already logged in!", client, channel));
	
	std::string password = params[0];
	if (password != client->getServer()->getPassword())
		return client->sendMessage(ft_formatmessage(ERR_PASSWDMISMATCH, "Wrong password.", client, channel));

	client->setLoggedIn(true);
	return client->sendMessage(ft_formatmessage(RPL_WELCOME, "Welcome to the IRC server!", client, channel));
};
