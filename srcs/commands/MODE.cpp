#include "MODE.hpp"

MODE::MODE(void) : Command("MODE", 2, true, true, false) {};
MODE::~MODE(void) {};

void MODE::run(Client *client, Channel *channel, std::vector<std::string> params)
{
	(void)channel;
	size_t param_count = 2;
	int clientID;
	Client *targetClient;

	Server	*server = client->getServer();
	Channel	*targetChannel = server->getChannelByName(params[0]);
	std::string mode = params[1];

	if (!targetChannel)
		return client->sendMessage(ft_formatmessage(ERR_NOSUCHCHANNEL, "No such channel", client), NULL);
	if (mode[0] == '+')
	{
		for (size_t i = 0; i < mode.length(); i++)
		{
			if (mode[i] == 'i')
				targetChannel->setInviteOnly(true);
			else if (mode[i] == 't')
				targetChannel->setTopicRestricted(true);
			else if (mode[i] == 'k')
			{
				if (params.size() < param_count + 1)
					return client->sendMessage(ft_formatmessage(ERR_NEEDMOREPARAMS, "Not enough parameters", client), NULL);
				targetChannel->setPassword(params[param_count]);
				targetChannel->setRestricted(true);
				param_count++;
			}
			else if (mode[i] == 'o')
			{
				if (params.size() < param_count + 1)
					return client->sendMessage(ft_formatmessage(ERR_NEEDMOREPARAMS, "Not enough parameters", client), NULL);
				targetClient = server->getClientByNickname(params[param_count]);
				if (targetClient == NULL)
					return client->sendMessage(ft_formatmessage(ERR_NOSUCHNICK, "No such nick", client), NULL);
				clientID = targetChannel->getID();
				targetChannel->OperatorPrivilege(true, clientID);
				param_count++;
			}
			else if (mode[i] == 'l')
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
		for (size_t i = 0; i < mode.length(); i++)
		{
			if (mode[i] == 'i')
				targetChannel->setInviteOnly(false);
			else if (mode[i] == 't')
				targetChannel->setTopicRestricted(false);
			else if (mode[i] == 'k')
			{
				targetChannel->setPassword("");
				targetChannel->setRestricted(false);
			}
			else if (mode[i] == 'o')
			{
				if (params.size() < param_count + 1)
					return client->sendMessage(ft_formatmessage(ERR_NEEDMOREPARAMS, "Not enough parameters", client), NULL);
				targetClient = server->getClientByNickname(params[param_count]);
				if (targetClient == NULL)
					return client->sendMessage(ft_formatmessage(ERR_NOSUCHNICK, "No such nick", client), NULL);
				clientID = targetClient->getID();
				targetChannel->OperatorPrivilege(false, clientID);
				param_count++;
			}
			else if (mode[i] == 'l')
			{
				targetChannel->setUserLimited(false);
				targetChannel->setMaxUser(-1);
			}
		}
	}


}

// MODE #channel -oo+b Alice Bob +v Charlie ??????????????????????
