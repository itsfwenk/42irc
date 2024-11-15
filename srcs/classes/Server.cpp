#include "Server.hpp"

bool Server::_running = false;
int Server::_exitStatus = 0;

Server::Server(std::string port, std::string password): _sockfd(0), _password(password) {
    int convertedPort = ft_get_converted_port(port);
    if (convertedPort == -1)
        throw std::invalid_argument("Wrong port argument, must be a number between 0 and 65535.");
    this->_port = convertedPort;

    // Signals handler
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = this->signalHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);
    signal(SIGTSTP, SIG_IGN);

    // Commands
    PASS* passCMD = new PASS;

    this->_commands.insert(std::pair<std::string, Command*>("PASS", passCMD));
};

Server::~Server(void) {
    for (std::map<const int, Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
        if (it->second)
            delete it->second;
    };

    for (std::map<const int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        if (it->second)
            delete it->second;
    };

    for (std::map<std::string, Command*>::iterator it = this->_commands.begin(); it != this->_commands.end(); it++) {
        if (it->second)
            delete it->second;
    };
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

bool const& Server::isRunning(void) {
    return this->_running;
};

int const& Server::getExitStatus(void) {
    return this->_exitStatus;
};

void Server::addChannel(Channel* channel) {
    Channel* channelExists = this->getChannelByID(channel->getID());
    if (channelExists) {
        delete channelExists;
        throw std::runtime_error("This channel is already on the list.");
    };
    this->_channels.insert(std::pair<const int, Channel*>(channel->getID(), channel));
};

void Server::addClient(Client* client) {
    Client* clientExists = this->getClientByID(client->getID());
    if (clientExists) {
        delete client;
        throw std::runtime_error("This client is already on the list.");
    };
    this->_clients.insert(std::pair<const int, Client*>(client->getID(), client));
};

void Server::rmChannel(int channelId) {
    Channel* channelExists = this->getChannelByID(channelId);
    if (channelExists) {
        delete channelExists;
        this->_channels.erase(channelId);
    };
};

void Server::rmClient(int clientId) {
    Client* clientExists = this->getClientByID(clientId);
    if (clientExists) {
        close(clientId);
        delete clientExists;
        this->_clients.erase(clientId);
    };
};

Channel* Server::getChannelByID(int channelId) {
    std::map<const int, Channel*>::iterator it = this->_channels.find(channelId);
    if (it == this->_channels.end())
        return NULL;
    return it->second;
};

Client* Server::getClientByID(int clientId) {
    std::map<const int, Client*>::iterator it = this->_clients.find(clientId);
    if (it == this->_clients.end())
        return NULL;
    return it->second;
};

Command* Server::getCommandByName(std::string name) {
    std::map<std::string, Command*>::iterator it = this->_commands.find(name);
    if (it == this->_commands.end())
        return NULL;
    return it->second;
};

Client* Server::getClientByNickname(std::string nickname) {
    for (std::map<const int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        if (it->second->getNickname() == nickname && it->second->isLoggedIn())
            return it->second;
    };
    throw std::invalid_argument("Cannot find any Client with this nickname.");
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
    int sockFD = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFD < 0)
        throw std::runtime_error("Cannot create the socket.");

    ft_setsockopts(sockFD);

    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->getPort());
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockFD, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(sockFD);
        throw std::runtime_error("Cannot bind the socket.");
    };

    if (listen(sockFD, MAX_CLIENTS) < 0) {
        close(sockFD);
        throw std::runtime_error("Cannot listen on the socket.");
    };

    this->_sockfd = sockFD;
    this->_running = true;

    std::ostringstream oss;
    oss << ntohs(server_addr.sin_port);
    ft_print_success("Server loaded successfully on port " + oss.str() + "! (Password: \"" + this->getPassword() + "\")");

    pollfd server_pollfd;
    memset(&server_pollfd, 0, sizeof(server_pollfd));
    server_pollfd.fd = sockFD;
    server_pollfd.events = POLLIN;

    std::vector<pollfd> pollfds;
    pollfds.push_back(server_pollfd);

    while (this->isRunning()) {
        int ret = poll(pollfds.data(), pollfds.size(), 500);
        if (ret < 0) {
            this->_running = false;
            break;
        };

        for (size_t i = 0; i < pollfds.size(); i++) {
            int pollFD = pollfds[i].fd;

            Client* selectedClient = this->getClientByID(pollFD);
            if (selectedClient && (!selectedClient->isLoggedIn() && std::time(NULL) - selectedClient->getAcceptedAt() >= 5)) {
                std::ostringstream oss;
                oss << pollFD;

                this->rmClient(pollFD);
                pollfds.erase(pollfds.begin() + i);
                ft_print_warning("Not identified client has just been logged out automatically! (ID " + oss.str() + ")");
                --i;
                continue;
            };

            if (pollfds[i].revents & POLLIN) {

                if (pollfds[i].fd == sockFD) {
                    int clientFD = accept(sockFD, NULL, NULL);
                    if (clientFD < 0) {
                        ft_print_warning("Cannot accept new client.");
                        continue;
                    };

                    ft_setsockopts(clientFD);

                    pollfd client_pollfd;
                    memset(&client_pollfd, 0, sizeof(client_pollfd));
                    client_pollfd.fd = clientFD;
                    client_pollfd.events = POLLIN;
                    pollfds.push_back(client_pollfd);

                    Client* newClient = new Client(clientFD, this);
                    this->addClient(newClient);

                    std::ostringstream oss;
                    oss << clientFD;
                    ft_print_success("New client connection! (ID " + oss.str() + ")");
                } else {
                    Client* selectedClient = this->getClientByID(pollfds[i].fd);
                    if (!selectedClient)
                        continue;

                    char buffer[1024] = {0};
                    int bytes_read = recv(pollFD, buffer, sizeof(buffer) - 1, 0);
                    if (bytes_read <= 0) {
                        std::ostringstream oss;
                        oss << pollFD;
                        this->rmClient(pollFD);
                        pollfds.erase(pollfds.begin() + i);
                        ft_print_warning("A client just logged out! (ID " + oss.str() + ")");
                        --i;
                    } else
                        selectedClient->parseMessageData(std::string(buffer));
                };
            };
        };
    };

    for (std::vector<pollfd>::iterator it = pollfds.begin(); it != pollfds.end(); it++)
        close(it->fd);
};
