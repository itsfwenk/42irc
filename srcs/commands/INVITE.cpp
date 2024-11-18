#include "INVITE.hpp"

INVITE::INVITE(void) : Command("INVITE", 2, true, true, false) {};
INVITE::~INVITE(void) {};

void INVITE::run(Client *client, Channel *channel, std::vector<std::string> params)
{
	(void)channel;

	Server	*server = client->getServer();
	Client	*toInvite = server->getClientByNickname(params[0]);
	Channel	*toChannel = server->getChannelByName(params[1]);

	if (!toInvite)
		return client->sendMessage(ft_formatmessage(ERR_NOSUCHNICK, "No such nick", client), NULL);
	if (!toChannel)
		return client->sendMessage(ft_formatmessage(ERR_NOSUCHCHANNEL, "No such channel", client), NULL);
	if (toChannel->isUserLimited())
	{
		if (toChannel->getClientIDs().size() == toChannel->getMaxUser())
			return client->sendMessage(ft_formatmessage(ERR_CHANNELISFULL, toChannel->getName() + " is full", client), NULL);
	}
	toChannel->getClientIDs().push_back(toInvite->getID());
	client->sendMessage(client->getNickname() + " INVITE " + params[0] + " to " + params[1], toChannel);
}
