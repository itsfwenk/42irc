#include "Channel.hpp"

Channel::Channel(Server* server) : _id(std::time(NULL)), _server(server)
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

std::vector<const int>	*Channel::getOperators(void)
{
	return &(this->_op);
}

std::vector<const int>	*Channel::getClientIDs(void)
{
	return &(this->_clientsIDs);
}

Server* Channel::getServer(void)
{
	return (this->_server);
}

bool Channel::isOperator(const int &clientID)
{
	std::vector<const int> operators = *this->getOperators();
	std::vector<const int>::iterator it = std::find(operators.begin(), operators.end(), clientID);

	return (it != operators.end());
}

int Channel::countOperators()
{
	std::vector<const int> op = *this->getOperators();
	return (op.size());
}

bool Channel::isInChannel(const int &clientID)
{
	std::vector<const int> channelClients = *this->getClientIDs();
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
void Channel::sendMessage(std::string message, Client *sender)
{
	Server* server = this->getServer();
	sender->sendMessage(message, this);
}
