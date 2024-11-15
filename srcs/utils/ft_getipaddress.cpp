#include "utils.hpp"

std::string ft_getipaddress(int sockfd) {
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);

    if (getsockname(sockfd, (struct sockaddr*)&addr, &addr_len) == -1)
        return "";

    char ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr.sin_addr, ip, sizeof(ip));
    return std::string(ip);
};
