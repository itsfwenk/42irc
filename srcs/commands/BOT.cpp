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
            return client->sendMessage("[RPN] The result of your RPN formula is: " + oss.str() + " !", channel);
        } catch (std::exception& err) {
            return client->sendMessage("[RPN] " + std::string(err.what()), channel);
        };
    } else if (command == "DICE") {
        std::ostringstream oss;
        oss << rand() % 6 + 1;
        return client->sendMessage("[DICE] The dice result is: " + oss.str() + " !", channel);
    } else if (command == "FLIP")
        return client->sendMessage("[FLIP] The flip result is: " + std::string(rand() % 2 ? "Heads" : "Tails") + " !", channel);
    else if (command == "TROLL")
        return client->sendMessage("Segmentation fault (Core trolled)", channel);
    else if (command == "SAY") {
        std::string say;

        for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); it++)
            say += *it + " ";

        return client->sendMessage("[SAY] " + client->getNickname() + " says: " + say, channel);
    } else if (command == "HELP") {
        std::string selectedCommand;

        if (params.size() >= 1)
            selectedCommand = params[1];

        if (selectedCommand.length()) {
            if (selectedCommand == "RPN")
                return client->sendMessage("[HELP RPN]: Usage: !bot RPN <RPN formula>, calculates the result of the RPN formula and returns it.", channel);
            else if (selectedCommand == "DICE")
                return client->sendMessage("[HELP DICE]: Usage: !bot DICE, rolls a 6-faces dice and returns the result.", channel);
            else if (selectedCommand == "FLIP")
                return client->sendMessage("[HELP FLIP]: Usage: !bot FLIP, flips a coin an returns if it is Heads or Tails.", channel);
            else if (selectedCommand == "TROLL")
                return client->sendMessage("[HELP TROLL]: Usage: !bot TROLL, ??? :).", channel);
            else if (selectedCommand == "SAY")
                return client->sendMessage("[HELP SAY]: Usage: !bot SAY <message>, says the message.", channel);
            else if (selectedCommand == "HELP")
                return client->sendMessage("[HELP HELP]: Usage: !bot HELP <bot cmd>, returns the list of bot commands if cmd is not specified or the informations about the bot command elsewise.", channel);
            else
                return client->sendMessage("[HELP]: Cannot find " + selectedCommand + " bot command.", channel);
        };

        return client->sendMessage("[HELP] Bot commands list: RPN, DICE, FLIP, TROLL, SAY, HELP", channel);
    };

    warning = "Cannot find " + command + " bot command.";
    client->sendMessage(ft_formatmessage(ERR_UNKNOWNCOMMAND, warning, client, channel), channel);
	ft_print_warning(warning);
};
