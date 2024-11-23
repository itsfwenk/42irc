#pragma once
#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ft_irc.hpp"

class Channel {
	private:
		std::string									_name;
		std::string									_topic;
		std::string									_password;
		std::vector<std::string>					_modes;
		int											_maxUsers;

		std::vector<int>							_operatorsClientsFds;	
		std::vector<int>							_joinedClientsFds;
		std::vector<int>							_invitedClientsFds;

		Server*										_server;

	public:
		Channel(std::string name, Server* server, Client* client);

		// Getters
		std::string const& getName(void);
		std::string const& getTopic(void);
		std::string const& getPassword(void);
		std::vector<std::string>& getModes(void);
		int const& getMaxUsers(void);

		std::vector<int>& getOperatorsClientsFds(void);
		std::vector<int>& getJoinedClientsFds(void);
		std::vector<int>& getInvitedClientsFds(void);

		bool isOperator(int clientFd);
		bool hasJoined(int clientFd);
		bool isInvited(int clientFd);
		bool hasMode(std::string mode);

		int getJoinedClientsCount(void);

		Server* getServer(void);

		// Setters
		void setTopic(std::string topic);
		void setPassword(std::string password);
		void addMode(std::string mode);
		void rmMode(std::string mode);
		void setMaxUsers(int maxUsers);

		void grantOperator(int clientFd);
		void ungrantOperator(int clientFd);
		void join(int clientFd);
		void part(int clientFd);
		void invite(int clientFd);
		void uninvite(int clientFd);
};

#endif
