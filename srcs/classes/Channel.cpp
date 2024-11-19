#include "Channel.hpp"

Channel::Channel(std::string name, Server* server) : _id(std::time(NULL)), _name(name), _server(server)
{
}

Channel::~Channel()
{
}

time_t const& Channel::getID(void)
{
	return this->_id;
};

int const& Channel::getMaxUser(void)
{
	return this->_maxUsers;
}

bool const& Channel::isUserLimited(void)
{
	return this->_userLimited;
}

bool const& Channel::isRestricted(void)
{
	return this->_restricted;
}

bool const& Channel::isInviteOnly(void)
{
	return this->_inviteOnly;
}

bool const& Channel::isTopicRestricted(void)
{
	return this->_topicRestricted;
}

std::string const& Channel::getPassword(void)
{
	return this->_password;
}

std::string const& Channel::getName(void)
{
	return this->_name;
}

std::string const& Channel::getTopic(void)
{
	return this->_topic;
}

std::vector<const int>	&Channel::getOperators(void)
{
	return this->_op;
}

std::vector<const int>	&Channel::getClientIDs(void)
{
	return this->_clientsIDs;
}

Server* Channel::getServer(void)
{
	return (this->_server);
}

bool Channel::isOperator(const int &clientID)
{
	std::vector<const int> operators = this->getOperators();
	std::vector<const int>::iterator it = std::find(operators.begin(), operators.end(), clientID);

	return (it != operators.end());
}

int Channel::countOperators()
{
	std::vector<const int> op = this->getOperators();
	return (op.size());
}

bool Channel::isInChannel(const int &clientID)
{
	std::vector<const int> channelClients = this->getClientIDs();
	std::vector<const int>::iterator it = std::find(channelClients.begin(), channelClients.end(), clientID);

	return (it != channelClients.end());
}

// void Channel::cmd_kick(Client	&executor, Client	&target)
// {
// 	if (Channel::isOperator(executor) == true
// 		&& Channel::countOperators() > 0)
// 	{

// 	}
// }
void Channel::sendMessage(std::string message)
{
	Server* server = this->getServer();
	std::map<const int, Client*>	clients = server->getClients();
	std::vector<const int> channelClientIDs = this->getClientIDs();

	for (std::vector<const int>::iterator it = channelClientIDs.begin(); it != channelClientIDs.end(); it++)
	{
		Client *user = server->getClientByID(it->first);
		if (user)
			user->sendMessage(message, NULL);
	}
}

void Channel::setInviteOnly(bool inviteOnly)
{
	this->_inviteOnly = inviteOnly;
}

void Channel::setTopicRestricted(bool topicRestricted)
{
	this->_topicRestricted = topicRestricted;
}

void Channel::setRestricted(bool restricted)
{
	this->_restricted = restricted;
}

void Channel::setPassword(std::string password)
{
	this->_password = password;
}

void Channel::OperatorPrivilege(bool grant, const int &clientID)
{
	if (grant)
		this->_op.push_back(clientID);
	else
		this->_op.erase(std::remove(this->_op.begin(), this->_op.end(), clientID), this->_op.end());
}

void Channel::setUserLimited(bool userLimited)
{
	this->_userLimited = userLimited;
}

void Channel::setMaxUser(int maxUser)
{
	this->_maxUsers = maxUser;
}

void Channel::rmClient(const int &clientID)
{
	std::vector<const int> &channelClientIDs = this->_clientsIDs;
	channelClientIDs.erase(std::remove(channelClientIDs.begin(), channelClientIDs.end(), clientID), channelClientIDs.end());
}
