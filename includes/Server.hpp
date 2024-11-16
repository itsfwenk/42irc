#pragma once
#ifndef SERVER_HPP
# define SERVER_HPP

# define MAX_CLIENTS 100
# define BUFFER_SIZE 1024
# define SERVER_NAME ":ft_irc "

# include <string>
# include <signal.h>
# include <cstring>
# include <poll.h>
# include <sstream>
# include <map>
# include <vector>

# include "Channel.hpp"
# include "Client.hpp"
# include "utils.hpp"

// Commands
# include "NICK.hpp"
# include "PASS.hpp"

class Command;
class Server {
    private:
        int                             _sockfd;
        int                             _port;
        std::string                     _password;
        static bool                     _running;
        static int                      _exitStatus;

        std::map<const int, Channel*>   _channels;
        std::map<const int, Client*>    _clients;
        std::map<std::string, Command*> _commands;

    public:
        Server(std::string port, std::string password);
        ~Server(void);

        void addChannel(Channel* channel);
        void addClient(Client* client);

        void rmChannel(int channelId);
        void rmClient(int clientId);

        // Getters
        int const& getSockFD(void);
        int const& getPort(void);
        std::string const& getPassword(void);
        bool const& isRunning(void);
        int const& getExitStatus(void);

        Channel* getChannelByID(int channelId);
        Client* getClientByID(int clientId);
        Client* getClientByNickname(std::string nickname);

        Command* getCommandByName(std::string name);

        // Setters
        static void signalHandler(int status);

        // Launcher
        void launch(void);
};

# include "Command.hpp"

#endif
