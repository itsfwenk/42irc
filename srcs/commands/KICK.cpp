#include "KICK.hpp"

KICK::KICK(void) : Command("KICK", 2, true, true, false) {};
KICK::~KICK(void) {};

void KICK::run(Client *client, Channel *channel, std::vector<std::string> params)
{
	(void)channel;

	Server *server = client->getServer();
	Channel	*fromChannel = server->getChannelByName(params[0]);
	Client *toKick = server->getClientByNickname(params[1]);

	if (client->getNickname() == toKick->getNickname())
		return client->sendMessage(ft_formatmessage(ERR_UNKNOWNCOMMAND, "Cannot self-kick", client), NULL);

	std::vector<const int> channelClientIDs = fromChannel->getClientIDs();
	if (params.size() >= 3)
		client->sendMessage("Kick " + toKick->getNickname() + " from " +  fromChannel->getName() + " : " + params[2], fromChannel);
	else
		client->sendMessage("Kick " + toKick->getNickname() + " from " +  fromChannel->getName(), fromChannel);
	channelClientIDs.erase(std::remove(channelClientIDs.begin(), channelClientIDs.end(), toKick->getID()), channelClientIDs.end());
}
