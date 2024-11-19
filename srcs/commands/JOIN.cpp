#include "JOIN.hpp"

JOIN::JOIN(void) : Command("JOIN", 1, false, true, false) {};
JOIN::~JOIN(void) {};

void JOIN::run(Client* client, Channel* channel, std::vector<std::string> params) {
	if (params.empty()) {
		client->sendMessage(ft_formatmessage(ERR_NEEDMOREPARAMS, "JOIN", client, channel), channel);
		return ;
	}

	std::string channelName = params[0];
	std::string password = (params.size() > 1) ? params[1] : "";

	Server* server = client->getServer();
	Channel* targetChannel = server->getChannelByName(channelName);
	if (!targetChannel)
	{
		targetChannel = new Channel(channelName, server);
		server->addChannel(targetChannel);
	}
	//isInChannel
	if (targetChannel->isInChannel(client->getID())) {
		client->sendMessage(": @localhost NOTICE " + client->getNickname() + " :You are already in " + channelName, channel);
		return ;
	}
	//isInviteOnly
	if (targetChannel->isInviteOnly()) {
		client->sendMessage(": @localhost NOTICE " + client->getNickname() + " :Cannot join channel " + channelName + " (Invite only)", channel);
		return;
	}
	//isUserLimited
	if (targetChannel->isUserLimited() && targetChannel->getClientIDs().size() >= targetChannel->getMaxUser()) {
		client->sendMessage(": @localhost NOTICE " + client->getNickname() + " :Cannot join channel " + channelName + " (Channel is full)", channel);
		return;
	}

	targetChannel->getClientIDs().push_back(client->getID());

	std::string joinMessage = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost JOIN :" + channelName;
	targetChannel->sendMessage(joinMessage);
	client->sendMessage(joinMessage, channel);

}
