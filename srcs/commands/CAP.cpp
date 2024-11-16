#include "CAP.hpp"

CAP::CAP(void): Command("CAP", 1, false, false, false) {};
CAP::~CAP(void) {};

void CAP::run(Client* client, Channel* channel, std::vector<std::string> params) {	
    std::string cmd = params[0];

    if (cmd == "REQ" || cmd == "DROP")
        return client->sendMessage("CAP * ACK :multi-prefix");
    else if (cmd == "LS" || cmd == "LIST")
        return client->sendMessage("CAP * LS :multi-prefix sasl away-notify");
    else if (cmd == "END")
        return client->sendMessage("ENDED");
    return client->sendMessage(ft_formatmessage(ERR_UNKNOWNCOMMAND, "Wrong parameter", client, channel));
};
