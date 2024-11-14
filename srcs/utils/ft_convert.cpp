#include "utils.hpp"

int ft_get_converted_port(std::string port) {
    for (size_t i = 0; i < port.length(); i++) {
        if (!isdigit(port[i]))
            return -1;
    };

    int converted = std::atoi(port.c_str());
    if (converted < 0 || converted > 65535)
        return -1;
    return converted;
};