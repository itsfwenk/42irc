#include "Server.hpp"

bool Server::_running = false;

Server::Server(std::string port, std::string password): _password(password) {
    int convertedPort = ft_get_converted_port(port);
    if (convertedPort == -1)
        throw std::invalid_argument("Wrong port argument, must be a number between 0 and 65535.");
    this->_port = convertedPort;

    std::string ipAddress = ft_getipaddress();
    if (ipAddress.empty())
        throw std::runtime_error("Cannot find host IP address.");
    this->_ipAddress = ipAddress;

    // Signals handler
    struct sigaction action;
    action.sa_handler = this->signalHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);
    signal(SIGTSTP, SIG_IGN);
};

// Getters
int const& Server::getPort(void) const {
    return this->_port;
};

std::string const& Server::getPassword(void) const {
    return this->_password;
};

std::string const& Server::getIPAddress(void) const {
    return this->_ipAddress;
};

bool const& Server::isRunning(void) const {
    return this->_running;
};

// Setters
void Server::signalHandler(int status) {
    (void)status;
    _running = false;
    ft_print_info("\nExit signal received, exiting...");
    _exit(128 + status);
};

// Launcher
void Server::launch(void) {
    this->_running = true;
    while (this->isRunning());
};
