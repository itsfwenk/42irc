#include "Server.hpp"

bool Server::_running = false;
int Server::_exitStatus = 0;

Server::Server(std::string port, std::string password): _sockfd(0), _password(password), _ipAddress("0.0.0.0") {
    int convertedPort = ft_get_converted_port(port);
    if (convertedPort == -1)
        throw std::invalid_argument("Wrong port argument, must be a number between 0 and 65535.");
    this->_port = convertedPort;

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
int const& Server::getSockFD(void) {
    return this->_sockfd;
};

int const& Server::getPort(void) {
    return this->_port;
};

std::string const& Server::getPassword(void) {
    return this->_password;
};

std::string const& Server::getIPAddress(void) {
    return this->_ipAddress;
};

bool const& Server::isRunning(void) {
    return this->_running;
};

int const& Server::getExitStatus(void) {
    return this->_exitStatus;
};

void Server::addChannel(Channel& channel) {
    try {
        this->getChannelByID(channel.getID());
        throw std::runtime_error("This channel is already on the list.");
    } catch (std::exception &e) {
        (void)e;
        this->_channels.insert(std::pair<const int, Channel&>(channel.getID(), channel));
    };
};

void Server::addClient(Client& client) {
    try {
        this->getChannelByID(client.getID());
        throw std::runtime_error("This channel is already on the list.");
    } catch (std::exception &e) {
        (void)e;
        this->_clients.insert(std::pair<const int, Client&>(client.getID(), client));
    };
};

void Server::rmChannel(int channelId) {
    try {
        this->getChannelByID(channelId);
        this->_channels.erase(channelId);
    } catch (std::exception &e) {
        throw e;
    };
};

void Server::rmClient(int clientId) {
    try {
        this->getClientByID(clientId);
        this->_clients.erase(clientId);
    } catch (std::exception &e) {
        throw e;
    };
};

Channel const& Server::getChannelByID(int channelId) {
    std::map<const int, Channel&>::const_iterator it = this->_channels.find(channelId);
    if (it == this->_channels.end())
        throw std::invalid_argument("Cannot find any Channel with this ID.");
    return it->second;
};

Client const& Server::getClientByID(int clientId) {
    std::map<const int, Client&>::const_iterator it = this->_clients.find(clientId);
    if (it == this->_clients.end())
        throw std::invalid_argument("Cannot find any Client with this ID.");
    return it->second;
};

// Setters
void Server::signalHandler(int status) {
    _running = false;
    _exitStatus = 128 + status;
    std::cout << std::endl;
    ft_print_info("Exit signal received, exiting...");
};

// Launcher
void Server::launch(void) {
    this->_running = true;
    while (this->isRunning());
};
