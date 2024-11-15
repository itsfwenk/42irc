#include "Client.hpp"

Client::Client(int id, Server* server): _id(id), _username("Default Username"), _nickname("Default nickname"), _loggedIn(false), _server(server) {};

// Getters
int const& Client::getID(void) {
	return this->_id;
};

std::string const& Client::getUsername(void) {
	return this->_username;
};

std::string const& Client::getNickname(void) {
	return this->_nickname;
};

bool const& Client::isLoggedIn(void) {
	return this->_loggedIn;
};

// Setters
void Client::parseMessageData(std::string messageData) {
	this->_messageData += messageData;
	size_t pos = 0;

    std::ostringstream oss;
	oss << this->getID();
	while ((pos = this->_messageData.find("\n", pos)) != std::string::npos) {
		std::string command = this->_messageData.substr(0, pos);
		ft_print_info("Data received from client ID " + oss.str() + "!\n");

		try {
			this->execCommand(command);
		} catch (std::exception &e) {
			ft_print_warning(e.what());
		};

		this->_messageData.erase(0, pos + 1);
	};
};

void Client::setUsername(std::string username) {
	this->_username = username;
};

void Client::setNickname(std::string nickname) {
	this->_nickname = nickname;
};

// Commands
void Client::execCommand(std::string command) {
	std::istringstream iss(command);
	
	std::string prefix;
	std::string cmd;
	std::vector<std::string> params;

	if (command[0] == ':')
		iss >> prefix;

	iss >> cmd;

	std::string param;
	while (iss >> param) {
		if (param[0] == ':') {
			std::string rest;
			std::getline(iss, rest);
			param += rest;
			break;
		};
		params.push_back(param);
	};

	this->sendMessage(cmd);
};

void Client::sendMessage(std::string message) {
	std::string formattedMessage = ":ft_irc " + message + "\r\n";
	std::ostringstream oss;
	oss << this->getID();
	ssize_t bytesSend = send(this->getID(), formattedMessage.c_str(), formattedMessage.size(), 0);
	if (bytesSend < 0)
		throw std::runtime_error("Cannot send message to client ID " + oss.str() + ".");
};
