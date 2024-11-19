#include "PRIVMSG.hpp"

PRIVMSG::PRIVMSG(void) : Command("PRIVMSG", 2, true, true, false) {};
PRIVMSG::~PRIVMSG(void) {};

void PRIVMSG::run(Client *client, Channel *channel, std::vector<std::string> params)
{
	(void)channel;

	Server *server = client->getServer();
	Channel	*toChannel;
	Client *toClient;

	if (params[0][0] == '#')
	{
		toChannel = server->getChannelByName(params[0]);
		if (!toChannel)
			return client->sendMessage(ft_formatmessage(ERR_NOSUCHCHANNEL, "No such channel", client), NULL);
		if (!toChannel->isInChannel(client->getID()))
			return client->sendMessage(ft_formatmessage(ERR_NOTONCHANNEL, "You're not in this channel", client), NULL);
		client->sendMessage(params[1], toChannel);
		return;
	}
	else
	{
		toClient = server->getClientByNickname(params[0]);
		if (!toClient)
			return client->sendMessage(ft_formatmessage(ERR_NOSUCHNICK, "No such nick", client), NULL);
		toClient->sendMessage(params[1], NULL);
		return;
	}
}
