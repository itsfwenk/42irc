#include "WHOIS.hpp"

WHOIS::WHOIS(void) : Command("WHOIS", 1, false, true, false) {};
WHOIS::~WHOIS(void) {};

void WHOIS::run(Client* client, Channel* channel, std::vector<std::string> params) {
	if (params.empty()) {
		client->sendMessage(ft_formatmessage(ERR_NEEDMOREPARAMS,"WHOIS", client, channel), channel);
		return ;
	}
	 std::string targetNick = params[0];
	 Server* server = client->getServer();
	 Client* target = server->getClientByNickname(targetNick);

	if (!target) {
		client->sendMessage(ft_formatmessage(ERR_NOSUCHNICK, targetNick, client, channel), channel);
		return;
	}

	// Contains the user's nickname, username, hostname, and real name.
	client->sendMessage(": @localhost 311 " + client->getNickname() + " " + target->getNickname() + " " + target->getUsername() + " * :", channel);

	// Contains the names of all channels the user has joined.
	client->sendMessage(": @localhost 319 " + client->getNickname() + " " + target->getNickname() + " :" + target->getJoinedChannelNames(), channel);

	// Contains the name of the server the user is connected to and its description.
	client->sendMessage(": @localhost 312 " + client->getNickname() + " " + target->getNickname() + " @localhost :Server Info", channel);

	// Indicates the end of the WHOIS response.
	client->sendMessage(": @localhost 318 " + client->getNickname() + " " + target->getNickname() + " :End of WHOIS list", channel);
};

