#include "MODE.hpp"

MODE::MODE(void) : Command("MODE", 2, true, true, false) {};
MODE::~MODE(void) {};

void MODE::run(Client *client, Channel *channel, std::vector<std::string> params)
{
	(void)channel;
	int param_count = 2;
	int clientID;

	Server	*server = client->getServer();
	Channel	*targetChannel = server->getChannelByName(params[0]);
	std::string mode = params[1];

	if (!targetChannel)
		return client->sendMessage(ft_formatmessage(ERR_NOSUCHCHANNEL, "No such channel", client), NULL);
	if (mode[0] == '+')
	{
		for (int i = 0; i < mode.length(); i++)
		{
			if (mode[i] == 'i')
				targetChannel->setInviteOnly(true);
			if (mode[i] == 't')
				targetChannel->setTopicRestricted(true);
			if (mode[i] == 'k')
			{
				if (params.size() < param_count + 1)
					return client->sendMessage(ft_formatmessage(ERR_NEEDMOREPARAMS, "Not enough parameters", client), NULL);
				targetChannel->setPassword(params[param_count]);
				targetChannel->setRestricted(true);
				param_count++;
			}
			if (mode[i] == 'o')
			{
				if (params.size() < param_count + 1)
					return client->sendMessage(ft_formatmessage(ERR_NEEDMOREPARAMS, "Not enough parameters", client), NULL);
				clientID = server->getClientByNickname(params[param_count])->getID();
				if (clientID == -1)
					return client->sendMessage(ft_formatmessage(ERR_NOSUCHNICK, "No such nick", client), NULL);
				targetChannel->OperatorPrivilege(true, clientID);
				param_count++;
			}
			if (mode[i] == 'l')
			{
				if (params.size() < param_count + 1)
					return client->sendMessage(ft_formatmessage(ERR_NEEDMOREPARAMS, "Not enough parameters", client), NULL);
				targetChannel->setUserLimited(true);
				long long newMaxUser = std::atoi(params[param_count].c_str());
				if (newMaxUser < 0 || newMaxUser > int(std::numeric_limits<int>::max()))
					return client->sendMessage(ft_formatmessage(ERR_NEEDMOREPARAMS, "Invalid parameter", client), NULL);
				targetChannel->setMaxUser(newMaxUser);
				param_count++;
			}
		}
	}
	else if (mode[0] == '-')
	{
		for (int i = 0; i < mode.length(); i++)
		{
			if (mode.find("i") != std::string::npos)
				targetChannel->setInviteOnly(false);
			if (mode.find("t") != std::string::npos)
				targetChannel->setTopicRestricted(false);
			if (mode.find("k") != std::string::npos)
			{
				targetChannel->setPassword("");
				targetChannel->setRestricted(false);
			}
			if (mode.find("o") != std::string::npos)
			{
				if (params.size() < param_count + 1)
					return client->sendMessage(ft_formatmessage(ERR_NEEDMOREPARAMS, "Not enough parameters", client), NULL);
				clientID = server->getClientByNickname(params[param_count])->getID();
				if (clientID == -1)
					return client->sendMessage(ft_formatmessage(ERR_NOSUCHNICK, "No such nick", client), NULL);
				targetChannel->OperatorPrivilege(false, clientID);
				param_count++;
			}
			if (mode.find("l") != std::string::npos)
			{
				targetChannel->setUserLimited(false);
				targetChannel->setMaxUser(-1);
			}
		}
	}


}

// MODE #channel -oo+b Alice Bob +v Charlie ??????????????????????
