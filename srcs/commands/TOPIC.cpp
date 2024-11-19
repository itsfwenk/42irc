#include "TOPIC.hpp"

TOPIC::TOPIC(void) : Command("TOPIC", 1, false, true, false) {};
TOPIC::~TOPIC(void) {};

void TOPIC::run(Client *client, Channel *channel, std::vector<std::string> params)
{
	(void)channel;

	Server	*server = client->getServer();
	Channel	*targetChannel = server->getChannelByName(params[0]);

	if (!targetChannel)
		return client->sendMessage(ft_formatmessage(ERR_NOSUCHCHANNEL, "No such channel", client), NULL);
	if (targetChannel->isTopicRestricted())
	{
		if (!targetChannel->isOperator(client->getID()))
			return client->sendMessage(ft_formatmessage(ERR_CHANOPRIVSNEEDED, "You're not a channel operator", client), NULL);
	}
	if (params.size() == 1)
		return client->sendMessage(targetChannel->getName() + " topic is " + targetChannel->getTopic(), NULL);

	std::string newTopic = params[1];
	return client->sendMessage(client->getNickname() + " setting " + targetChannel->getName() + " topic to " + newTopic, targetChannel);
}

// https://www.rfc-editor.org/rfc/rfc2812#section-3.2.4
