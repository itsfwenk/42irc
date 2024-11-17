#include "PING.hpp"

PING::PING(void): Command("PING", 1, false, false, false) {};
PING::~PING(void) {};

void PING::run(Client* client, Channel* channel, std::vector<std::string> params) {
    return client->sendMessage(params[0], channel);
};
