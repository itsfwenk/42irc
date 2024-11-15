#include "Client.hpp"

Client::Client(int id): _id(id) {};

// Getters
int const& Client::getID(void) {
	return this->_id;
};

// Setters
void Client::parseMessageData(std::string messageData) {
	this->_messageData += messageData;
	size_t pos = 0;

    std::ostringstream oss;
	oss << this->getID();
	while ((pos = this->_messageData.find("\n", pos)) != std::string::npos) {
		std::string command = this->_messageData.substr(0, pos);
		ft_print_info("Data received from client ID " + oss.str() + "!");
		std::cout << command << std::endl;
		this->_messageData.erase(0, pos + 1);
	};
};
