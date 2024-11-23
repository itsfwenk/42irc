#include "Channel.hpp"

Channel::Channel(std::string name, Server* server, Client* client): _name(name), _server(server) {
	int clientFd = client->getFd();
	
	this->_joinedClientsFds.push_back(clientFd);
	this->_joinedClientsFds.push_back(server->getBot()->getFd());
	this->_operatorsClientsFds.push_back(clientFd);
	client->joinChannel(name);

	print_info(name + " channel created successfully!");
};

// Getters
std::string const& Channel::getName(void) {
	return this->_name;
};

std::string const& Channel::getTopic(void) {
	return this->_topic;
};

std::string const& Channel::getPassword(void) {
	return this->_password;
};

std::vector<std::string>& Channel::getModes(void) {
	return this->_modes;
};

int const& Channel::getMaxUsers(void) {
	return this->_maxUsers;
};

std::vector<int>& Channel::getOperatorsClientsFds(void) {
	return this->_operatorsClientsFds;
};

std::vector<int>& Channel::getJoinedClientsFds(void) {
	return this->_joinedClientsFds;
};

std::vector<int>& Channel::getInvitedClientsFds(void) {
	return this->_invitedClientsFds;
};

bool Channel::isOperator(int clientFd) {
	std::vector<int>& operatorsClientsFds = this->getOperatorsClientsFds();
	std::vector<int>::iterator it = std::find(operatorsClientsFds.begin(), operatorsClientsFds.end(), clientFd);
	return it != operatorsClientsFds.end();
};

bool Channel::hasJoined(int clientFd) {
	std::vector<int>& joinedClientsFds = this->getJoinedClientsFds();
	std::vector<int>::iterator it = std::find(joinedClientsFds.begin(), joinedClientsFds.end(), clientFd);
	return it != joinedClientsFds.end();
};

bool Channel::isInvited(int clientFd) {
	std::vector<int>& invitedClientsFds = this->getInvitedClientsFds();
	std::vector<int>::iterator it = std::find(invitedClientsFds.begin(), invitedClientsFds.end(), clientFd);
	return it != invitedClientsFds.end();
};

bool Channel::hasMode(std::string mode) {
	std::vector<std::string>& modes = this->getModes();
	std::vector<std::string>::iterator it = std::find(modes.begin(), modes.end(), mode);
	return it != modes.end();
};

int Channel::getJoinedClientsCount(void) {
	std::vector<int>& joinedClientsFds = this->getJoinedClientsFds();
	return (int)joinedClientsFds.size();
};

Server* Channel::getServer(void) {
	return this->_server;
};

// Setters
void Channel::setTopic(std::string topic) {
	this->_topic = topic;
};

void Channel::setPassword(std::string password) {
	this->_password = password;
};

void Channel::addMode(std::string mode) {
	std::vector<std::string>& modes = this->getModes();
	modes.push_back(mode);
};

void Channel::rmMode(std::string mode) {
	std::vector<std::string>& modes = this->getModes();
	std::vector<std::string>::iterator it = std::find(modes.begin(), modes.end(), mode);
	if (it != modes.end())
		modes.erase(it);
};

void Channel::setMaxUsers(int maxUsers) {
	this->_maxUsers = maxUsers;
};

void Channel::grantOperator(int clientFd) {
	std::vector<int>& operatorsClientsFds = this->getOperatorsClientsFds();
	operatorsClientsFds.push_back(clientFd);
};

void Channel::ungrantOperator(int clientFd) {
	std::vector<int>& operatorsClientsFds = this->getOperatorsClientsFds();
	std::vector<int>::iterator it = std::find(operatorsClientsFds.begin(), operatorsClientsFds.end(), clientFd);
	if (it != operatorsClientsFds.end())
		operatorsClientsFds.erase(it);
};

void Channel::join(int clientFd) {
	std::vector<int>& joinedClientsFds = this->getJoinedClientsFds();
	joinedClientsFds.push_back(clientFd);
};

void Channel::part(int clientFd) {
	Server* server = this->getServer();
	std::vector<int>& joinedClientsFds = this->getJoinedClientsFds();
	std::vector<int>::iterator it = std::find(joinedClientsFds.begin(), joinedClientsFds.end(), clientFd);
	if (it != joinedClientsFds.end())
		joinedClientsFds.erase(it);
	if (!joinedClientsFds.size()) {
		std::string name = this->getName();
		server->rmChannel(name);
		print_info(name + " channel has been removed! (No more clients inside)");
	};
};

void Channel::invite(int clientFd) {
	std::vector<int>& invitedClientsFds = this->getInvitedClientsFds();
	invitedClientsFds.push_back(clientFd);
};

void Channel::uninvite(int clientFd) {
	std::vector<int>& invitedClientsFds = this->getInvitedClientsFds();
	std::vector<int>::iterator it = std::find(invitedClientsFds.begin(), invitedClientsFds.end(), clientFd);
	if (it != invitedClientsFds.end())
		invitedClientsFds.erase(it);
};
