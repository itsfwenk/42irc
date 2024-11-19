#include "QUIT.hpp"

QUIT::QUIT(void): Command("QUIT", 0, false, false, false) {};
QUIT::~QUIT(void) {};

void QUIT::run(Client* client, Channel* channel, std::vector<std::string> params) {
	(void)channel;
	std::string quitMessage = params.empty() ? "Client Quit" : params[0];

	std::string message = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost QUIT :" + quitMessage;

	client->sendMessageToMyChannels(quitMessage);
};
