#include "NICK.hpp"

NICK::NICK(void): Command("NICK", 1, false, false) {};
NICK::~NICK(void) {};

void NICK::run(Client* client, std::vector<std::string> params) {	
    std::string oldnickname = client->getNickname();
	std::string nickname = params[0];

    if (!nickname.length()) {
        return client->sendMessage(ft_formatmessage(ERR_NONICKNAMEGIVEN, "No nickname given.", client));
    };

	try {
        client->setNickname(nickname);
    } catch (std::exception &err) {
        return client->sendMessage(ft_formatmessage(ERR_NICKNAMEINUSE, err.what(), client));
    };

    return client->sendMessage(": " + oldnickname + " NICK :" + nickname);
};
