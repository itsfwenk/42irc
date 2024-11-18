#include "Server.hpp"

bool Server::_running = false;
int Server::_exitStatus = 0;

Server::Server(std::string port, std::string password): _sockfd(0) {
    int convertedPort = ft_get_converted_port(port);
    if (convertedPort == -1)
        throw std::invalid_argument("Wrong port argument, must be a number between 0 and 65535.");
    this->_port = convertedPort;

    if (password.empty())
        throw std::invalid_argument("Password cannot be empty.");
    this->_password = password;

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
    this->_commands.insert(std::pair<std::string, Command*>("!bot", new BOT));
    this->_commands.insert(std::pair<std::string, Command*>("CAP", new CAP));
    this->_commands.insert(std::pair<std::string, Command*>("NICK", new NICK));
    this->_commands.insert(std::pair<std::string, Command*>("PASS", new PASS));
    this->_commands.insert(std::pair<std::string, Command*>("PING", new PING));
};

Server::~Server(void) {
    std::map<const int, Channel*> channels = this->getChannels();
    for (std::map<const int, Channel*>::iterator it = channels.begin(); it != channels.end(); it++) {
        if (it->second)
            delete it->second;
    };

    std::map<const int, Client*>& clients = this->getClients();
    for (std::map<const int, Client*>::iterator it = clients.begin(); it != clients.end(); it++) {
        if (it->second)
            delete it->second;
    };

    std::map<std::string, Command*> commands = this->getCommands();
    for (std::map<std::string, Command*>::iterator it = commands.begin(); it != commands.end(); it++) {
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
    std::map<const int, Channel*>& channels = this->getChannels();
    Channel* channelExists = this->getChannelByID(channel->getID());
    if (channelExists) {
        delete channelExists;
        throw std::runtime_error("This channel is already on the list.");
    };
    channels.insert(std::pair<const int, Channel*>(channel->getID(), channel));
};

void Server::addClient(Client* client) {
    std::map<const int, Client*>& clients = this->getClients();
    Client* clientExists = this->getClientByID(client->getID());
    if (clientExists) {
        delete client;
        throw std::runtime_error("This client is already on the list.");
    };
    clients.insert(std::pair<const int, Client*>(client->getID(), client));
};

void Server::rmChannel(int channelId) {
    std::map<const int, Channel*>& channels = this->getChannels();
    Channel* channelExists = this->getChannelByID(channelId);
    if (channelExists) {
        delete channelExists;
        channels.erase(channelId);
    };
};

void Server::rmClient(int clientId) {
    std::map<const int, Client*>& clients = this->getClients();
    Client* clientExists = this->getClientByID(clientId);
    if (clientExists) {
        close(clientId);
        delete clientExists;
        clients.erase(clientId);
    };
};

Channel* Server::getChannelByID(int channelId) {
    std::map<const int, Channel*> channels = this->getChannels();
    std::map<const int, Channel*>::iterator it = channels.find(channelId);
    if (it == channels.end())
        return NULL;
    return it->second;
};

Client* Server::getClientByID(int clientId) {
    std::map<const int, Client*> clients = this->getClients();
    std::map<const int, Client*>::iterator it = clients.find(clientId);
    if (it == clients.end())
        return NULL;
    return it->second;
};

Command* Server::getCommandByName(std::string name) {
    std::map<std::string, Command*> commands = this->getCommands();
    std::map<std::string, Command*>::iterator it = commands.find(name);
    if (it == commands.end())
        return NULL;
    return it->second;
};

Client* Server::getClientByNickname(std::string nickname) {
    std::map<const int, Client*> clients = this->getClients();
    for (std::map<const int, Client*>::iterator it = clients.begin(); it != clients.end(); it++) {
        if (it->second->getNickname() == nickname && it->second->isLoggedIn())
            return it->second;
    };
    return NULL;
};

Channel* Server::getChannelByName(std::string name) {
    std::map<const int, Channel*> channels = this->getChannels();
    for (std::map<const int, Channel*>::iterator it = channels.begin(); it != channels.end(); it++) {
        if (it->second->getName() == name)
            return it->second;
    };
    return NULL;
};

std::map<const int, Channel*>& Server::getChannels(void) {
    return this->_channels;
};

std::map<const int, Client*>& Server::getClients(void) {
    return this->_clients;
};

std::map<std::string, Command*>& Server::getCommands(void) {
    return this->_commands;
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

void Server::sendMessage(std::string message) {
    std::map<const int, Client*> clients = this->getClients();
    for (std::map<const int, Client*>::iterator it = clients.begin(); it != clients.end(); it++) {
        if (it->second)
            it->second->sendMessage(message, NULL); 
    };
};