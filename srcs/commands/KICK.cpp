#include "KICK.hpp"

KICK::KICK(void) : Command("KICK", 2, true, true, true) {};
KICK::~KICK(void) {};

void KICK::run(Client *client, Channel *channel, std::vector<std::string> params)
{
	(void)channel;

	Server *server = client->getServer();
	Channel	*fromChannel = server->getChannelByName(params[0]);
	Client *toKick = server->getClientByNickname(params[1]);
	if (params.size() >= 3)
		std::string comment = params[2];

	if (client->getNickname() == toKick->getNickname())
		return client->sendMessage(ft_formatmessage(ERR_UNKNOWNCOMMAND, "Cannot self-kick", client), NULL);
	else if (!fromChannel->isOperator(client->getID()))
		return client->sendMessage(ft_formatmessage(ERR_CHANOPRIVSNEEDED, "You're not channel operator", client), NULL);
	else if (!fromChannel->isInChannel(client->getID()))
		return client->sendMessage(ft_formatmessage(ERR_USERNOTINCHANNEL, "User not in channel", client), NULL);

	std::vector<const int> *channelClientIDs = fromChannel->getClientIDs();
	channelClientIDs->erase(std::remove(channelClientIDs->begin(), channelClientIDs->end(), toKick->getID()), channelClientIDs->end());
}
