#include "Channel.hpp"

Channel::Channel()
{
}

Channel::~Channel()
{
}

int const& Channel::getID(void)
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

std::vector<Client	&>	Channel::getOperators(void)
{
	return this->_op;
}

std::vector<const int>	Channel::getClientIDs(void)
{
	return this->_clientsIDs;
}
