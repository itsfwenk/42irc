#pragma once
#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <sstream>
# include <ctime>
# include "utils.hpp"

class Server;
class Client {
	private:
		int 			_id;
		std::string		_username;
		std::string		_nickname;
		bool			_loggedIn;
		time_t			_acceptedAt;
		std::string		_messageData;
		Server*			_server;

	public:
		Client(int id, Server* server);

		// Getters
		int const& getID(void);
		std::string const& getUsername(void);
		std::string const& getNickname(void);
		time_t const& getAcceptedAt(void);
		bool const& isLoggedIn(void);
		Server* getServer(void);

		// Setters
		void parseMessageData(std::string messageData);
		void setUsername(std::string username);
		void setNickname(std::string nickname);
		void setLoggedIn(bool loggedIn);

		// Commands
		void execCommand(std::string command);
		void sendMessage(std::string message);
};

# include "Server.hpp"

#endif
