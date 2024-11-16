#include "CAP.hpp"

CAP::CAP(void): Command("CAP", 1, false, false) {};
CAP::~CAP(void) {};

void CAP::run(Client* client, std::vector<std::string> params) {	
    std::string cmd = params[0];

    std::cout << cmd << std::endl;
    if (cmd == "REQ" || cmd == "DROP")
        return client->sendMessage("CAP * ACK :multi-prefix");
    else if (cmd == "LS" || cmd == "LIST")
        return client->sendMessage("CAP * LS :multi-prefix sasl away-notify");
    else if (cmd == "END")
        return client->sendMessage("ENDED");
    return client->sendMessage(ft_formatmessage(ERR_UNKNOWNCOMMAND, "Wrong parameter", client));
};
