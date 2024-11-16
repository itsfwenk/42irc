#include "Channel.hpp"

Channel::Channel()
{
}

Channel::~Channel()
{
}

int const& Channel::getID(void) {
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

std::string const& Channel::getName(void) {
	return this->_name;
};
