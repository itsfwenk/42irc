#pragma once
#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <signal.h>
# include <vector>
# include <exception>
# include <ctime>
# include <algorithm>

# include "Client.hpp"
# include "utils.hpp"

class Channel {
	private:
		time_t					_id;
		int						_maxUsers;
		bool					_userLimited;
		bool					_restricted;
		bool					_inviteOnly;
		bool					_topicRestricted;
		std::string				_password;
		std::string				_name;
		std::string				_topic;
		std::vector<const int>	_op;
		std::vector<const int>	_clientsIDs;

		Server*					_server;

	public:
		Channel(Server* server);
		~Channel();

		//Accessors
		time_t const& getID(void);
		int const& getMaxUser(void);
		bool const& isUserLimited(void);
		bool const& isRestricted(void);
		bool const& isInviteOnly(void);
		bool const& isTopicRestricted(void);
		std::string const& getPassword(void);
		std::string const& getName(void);
		std::string const& getTopic(void);
		std::vector<const int>	&getOperators(void);
		std::vector<const int>	&getClientIDs(void);
		Server* getServer(void);

		bool isOperator(const int &clientID);
		int countOperators();

		bool isInChannel(const int &clientID);

		void sendMessage(std::string message);

		void rmClient(const int &clientID);

		//COMMAND
		// void cmd_kick(Client	&executor, Client	&target);
		// void cmd_invite(Client	&executor, Client	&target);
		// void cmd_topic(Client	&executor, std::string topic);
		// void cmd_mode(Client	&executor, std::string mode);

		//Setters
		//i Set/remove Invite-only channel
		void setInviteOnly(bool inviteOnly);

		//t Set/remove the restrictions of the TOPIC command to channel operators
		void setTopicRestricted(bool topicRestricted);

		//k Set/remove the channel key (password)
		void setRestricted(bool restricted);
		void setPassword(std::string password);

		//o Give/take channel operator privilege
		void OperatorPrivilege(bool grant, const int &clientID);

		//l Set/remove the user limit to channel
		void setUserLimited(bool userLimited);
		void setMaxUser(int maxUser);
};

#endif
