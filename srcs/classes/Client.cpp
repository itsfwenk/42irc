#include "Client.hpp"

Client::Client(int id, Server* server): _id(id), _username("username"), _nickname("nickname"), _loggedIn(false), _acceptedAt(std::time(NULL)), _server(server) {};

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

time_t const& Client::getAcceptedAt(void) {
	return this->_acceptedAt;
};

Server* Client::getServer(void) {
	return this->_server;
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
		ft_print_info("Data received from client ID " + oss.str() + " (" + this->getNickname() + ") !");
		try {
			this->execCommand(command);
		} catch (std::exception& err) {
			ft_print_warning(err.what());
		};
		this->_messageData.erase(0, pos + 1);
	};
};

void Client::setUsername(std::string username) {
	this->_username = username;
};

void Client::setNickname(std::string nickname) {
	Server* server = this->getServer();
	Client* client = server->getClientByNickname(nickname);

	if (client)
		throw std::invalid_argument("This nickname is already used!");
	else if (nickname == "nickname")
		throw std::invalid_argument("This nickname cannot be used!");

	this->_nickname = nickname;
};

void Client::setLoggedIn(bool loggedIn) {
	this->_loggedIn = loggedIn;
};

// Commands
void Client::execCommand(std::string command) {
	Server* server = this->getServer();
	std::istringstream iss(command);
	
	std::string prefix;
	std::string cmd;
	std::vector<std::string> params;

	if (command[0] == ':')
		iss >> prefix;

	iss >> cmd;
	if (!cmd.length())
		throw std::invalid_argument("Empty command.");

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

	Command* selectedCommand = server->getCommandByName(cmd);
	Channel* selectedChannel = params.size() ? server->getChannelByName(params[0]) : NULL;
	std::string warning;

	if (selectedChannel)
		params.erase(params.begin());

	if (selectedCommand) {
		std::ostringstream oss;
		oss << selectedCommand->getReqArgs();

		if ((size_t)selectedCommand->getReqArgs() > params.size())
			warning = "Command " + cmd + ": wrong number of argumets (expected at least " + oss.str() + " argument(s))";
		else if (selectedCommand->mustBeLogged() && !this->isLoggedIn())
			warning = "You must be logged in to run this command!";
		else if (selectedCommand->insideChannel() && !selectedChannel)
			warning = "You must be inside a channel to run this command!";
		else if (selectedCommand->isOpCMD()) {
			// Vérifier si on est dans un salon valide.
			// Vérifier si le client est un OP.
		};

		if (warning.length()) {
			this->sendMessage(ft_formatmessage(ERR_UNKNOWNCOMMAND, warning, this, selectedChannel));
			throw std::invalid_argument(warning);
		};

		if (cmd == "!bot")
			ft_print_info(this->getNickname() + " is using " + params[0] + " bot command!");
		else
			ft_print_info(this->getNickname() + " is using " + selectedCommand->getName() + " command!");

		selectedCommand->run(this, selectedChannel, params);
	} else {
		warning = "Cannot find " + cmd + " command.";
		this->sendMessage(ft_formatmessage(ERR_UNKNOWNCOMMAND, warning, this, selectedChannel));
		ft_print_warning(warning);
	};
};

void Client::sendMessage(std::string message) {
	std::string formattedMessage = message + "\r\n";
	std::ostringstream oss;
	oss << this->getID();
	send(this->getID(), formattedMessage.c_str(), formattedMessage.size(), MSG_NOSIGNAL);
};
