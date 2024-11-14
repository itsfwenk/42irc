#pragma once
#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <signal.h>
# include "utils.hpp"

class Server {
    private:
        int             _port;
        std::string     _password;
        std::string     _ipAddress;
        static bool     _running;

    public:
        Server(std::string port, std::string password);

        // Getters
        int const& getPort(void) const;
        std::string const& getPassword(void) const;
        std::string const& getIPAddress(void) const;
        bool const& isRunning(void) const;

        // Setters
        static void signalHandler(int status);

        // Launcher
        void launch(void);
};

#endif