#include "utils.hpp"

std::string ft_getipaddress(void) {
    struct ifaddrs *ifAddrStruct = NULL;
    struct ifaddrs *ifa = NULL;
    void *tmpAddrPtr = NULL;
    
    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr->sa_family == AF_INET) {
            tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            
            if (std::string(ifa->ifa_name) == "eth0" || std::string(ifa->ifa_name) == "wlan0") {
                std::string ipAddress(addressBuffer);
                freeifaddrs(ifAddrStruct);
                return ipAddress;
            };
        };
    };

    freeifaddrs(ifAddrStruct);
    return "";
};