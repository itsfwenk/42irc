#pragma once
#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"

class Client;
class Channel;
class Command;

struct execReturnData;

class Server {
	private:
		int			_fd;
		int			_port;
		std::string	_password;
		time_t		_launchedAt;

		std::map<int, Client> _clients;
		std::map<std::string, Command*> _commands;
		std::map<std::string, Channel> _channels;
		std::vector<pollfd> _pollFds;

		static bool	_isRunning;
		static int	_exitStatus;

	public:
		Server(std::string port, std::string password);

		// Getters
		int const& getFd(void);
		int const& getPort(void);
		std::string const& getPassword(void);
		time_t const& getLaunchedAt(void);

		std::map<int, Client>& getClients(void);
		std::map<std::string, Command*>& getCommands(void);
		std::map<std::string, Channel>& getChannels(void);
		std::vector<pollfd>& getPollFds(void);

		bool const& isRunning(void);
		int const& getExitStatus(void);

		pollfd getServerPollFd(void);

		bool isNicknameAlreadyUsed(std::string nickname);
		bool isChannelNameAlreadyUsed(std::string name);

		std::vector<int> getClientsFds(void);

		// Getters by value
		Client* getClientByFd(int clientFd);
		Client* getClientByNickname(std::string nickname);

		Command* getCommandByName(std::string name);

		Channel* getChannelByName(std::string name);
 
		// Setters
		void setFd(int fd);
		void setLaunchedAt(time_t launchedAt);

		void setIsRunning(bool isRunning);
		void setExitStatus(int exitStatus);
		void setupSignals(void);
		void setupCommands(void);

		void rmClient(int clientFd);
		void rmChannel(std::string name);

		// Static
		static int validatePort(std::string port);
		static std::string validatePassword(std::string password);
		static void signalHandler(int status);
		static void setSocketOptions(int socketFd);
		static pollfd getClientPollFd(int clientFd);

		static execReturnData createBasicExecReturnData(int fd);
	
		static bool isCorrectNickname(std::string nickname);
		static bool isCorrectChannelName(std::string name);
		static bool isCorrectTopic(std::string topic);
		static bool containsForbiddenChararacters(std::string str);

		// Launcher
		void launch(void);
		void cleanup(void);
};

# include "Channel.hpp"
# include "Client.hpp"

#endif
