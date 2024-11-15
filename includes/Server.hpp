#pragma once
#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <signal.h>
# include <map>

# include "Channel.hpp"
# include "Client.hpp"
# include "utils.hpp"

class Server {
    private:
        int                            _sockfd;
        int                            _port;
        std::string                    _password;
        std::string                    _ipAddress;
        static bool                    _running;
        static int                     _exitStatus;

        std::map<const int, Channel&>  _channels;
        std::map<const int, Client&>   _clients;

    public:
        Server(std::string port, std::string password);

        void addChannel(Channel& channel);
        void addClient(Client& client);

        void rmChannel(int channelId);
        void rmClient(int clientId);

        // Getters
        int const& getSockFD(void);
        int const& getPort(void);
        std::string const& getPassword(void);
        std::string const& getIPAddress(void);
        bool const& isRunning(void);
        int const& getExitStatus(void);

        Channel const& getChannelByID(int channelId);
        Client  const& getClientByID(int clientId);

        // Setters
        static void signalHandler(int status);

        // Launcher
        void launch(void);
};

#endif
