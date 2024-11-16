#include "NICK.hpp"

NICK::NICK(void): Command("NICK", 1, false, false, false) {};
NICK::~NICK(void) {};

void NICK::run(Client* client, Channel* channel, std::vector<std::string> params) {	
    std::string oldnickname = client->getNickname();
	std::string nickname = params[0];

    if (!nickname.length()) {
        return client->sendMessage(ft_formatmessage(ERR_NONICKNAMEGIVEN, "No nickname given.", client, channel));
    };

	try {
        client->setNickname(nickname);
    } catch (std::exception &err) {
        (void)err;
        return client->sendMessage(ft_formatmessage(ERR_NICKNAMEINUSE, nickname, client, channel));
    };

    return client->sendMessage(":" + oldnickname + "!" + client->getUsername() + "@localhost NICK " + nickname);
};
