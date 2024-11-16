#include "BOT.hpp"

BOT::BOT(void): Command("BOT", 1, false, false, false) {};
BOT::~BOT(void) {};

void BOT::run(Client* client, Channel* channel, std::vector<std::string> params) {
    std::string command = params[0];
    std::string warning;

    params.erase(params.begin());

    if (command == "RPN") {
        std::string rpn;

        for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); it++)
            rpn += *it + " ";

        try {
            std::ostringstream oss;
            oss << RPN::doRPN(rpn);
            return client->sendMessage("[RPN] The result of your RPN formula is: " + oss.str() + " !");
        } catch (std::exception& err) {
            return client->sendMessage("[RPN] " + std::string(err.what()));
        };
    };

    warning = "Cannot find " + command + " bot command.";
    client->sendMessage(ft_formatmessage(ERR_UNKNOWNCOMMAND, warning, client, channel));
	ft_print_warning(warning);
};
