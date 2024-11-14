#include "Server.hpp"

int main(int argc, char** argv) {
    ft_print_logo();

    if (argc != 3) {
        ft_print_error("Bad number of arguments, ./ircserv [PORT] [PASSWORD]");
        return 1;
    };

    std::string port = argv[1];
    std::string password = argv[2];

    try {
        Server IRC_Server = Server(port, password);
        IRC_Server.launch();
    } catch (std::exception const& err) {
        ft_print_error(err.what());
        return 1;
    };
    
    ft_print_info("Exiting...");
    return 0;
};